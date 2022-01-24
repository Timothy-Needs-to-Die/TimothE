#include "Renderer2D.h"

struct QuadVertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
	float texIndex;
	float tilingFactor;

	//TODO: this is editor side handle this
	int entityID;
};

struct RendererData {
	static const unsigned int maxQuads = 20000;
	static const unsigned int maxVertices = maxQuads * 4;
	static const unsigned int maxIndices = maxQuads * 6;
	static const unsigned int maxTextureSlots = 32;

	std::shared_ptr<VAO> quadVertexArray;
	std::shared_ptr<VBO> quadVertexBuffer;
	std::shared_ptr<Shader> textureShader;
	Texture2D* whiteTexture;

	unsigned int quadIndexCount;
	QuadVertex* quadVertexBufferBase = nullptr;
	QuadVertex* quadVertexBufferPtr = nullptr;

	//TODO: Replace 32 with a fixed size
	std::array <Texture2D*, 32> textureSlots;
	unsigned int textureSlotIndex = 1; //0 = white texture

	glm::vec4 quadVertexPositions[4];
};

static RendererData _data;

static Camera* currentCam;


void Renderer2D::Init()
{
	_data.quadVertexArray = VAO::Create();

	_data.quadVertexBuffer = VBO::Create(_data.maxVertices * sizeof(QuadVertex));
	_data.quadVertexBuffer->SetLayout({
			{ ShaderDataTypes::Float3, "a_Position"     },
			{ ShaderDataTypes::Float4, "a_Color"        },
			{ ShaderDataTypes::Float2, "a_TexCoord"     },
			{ ShaderDataTypes::Float,  "a_TexIndex"     },
			{ ShaderDataTypes::Float,  "a_TilingFactor" },
			{ ShaderDataTypes::Int,    "a_EntityID"     }
		});

	_data.quadVertexArray->AddVertexBuffer(_data.quadVertexBuffer);
	_data.quadVertexBufferBase = new QuadVertex[_data.maxVertices];

	unsigned int* quadIndices = new unsigned int[_data.maxIndices];

	unsigned int offset = 0;
	for (unsigned int i = 0; i < _data.maxIndices; i += 6) {
		quadIndices[i + 0] = offset + 0;
		quadIndices[i + 1] = offset + 1;
		quadIndices[i + 2] = offset + 2;

		quadIndices[i + 3] = offset + 2;
		quadIndices[i + 4] = offset + 3;
		quadIndices[i + 5] = offset + 0;

		offset += 4;
	}

	std::shared_ptr<IBO> quadIB = IBO::Create(quadIndices, _data.maxIndices);

	_data.quadVertexArray->SetIndexBuffer(quadIB);
	delete[] quadIndices;

	_data.whiteTexture = new Texture2D("whiteTexture.png");

	unsigned int samplers[_data.maxTextureSlots];
	for (unsigned int i = 0; i < _data.maxTextureSlots; i++) {
		samplers[i] = i;
	}

	_data.textureShader = std::make_shared<Shader>("vs_Texture.vert", "fr_Texture.frag");
	
	_data.textureSlots[0] = _data.whiteTexture;

	_data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	_data.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
	_data.quadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
	_data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

}

void Renderer2D::Shutdown()
{
	//delete[] _data.quadVertexBuffer;
}

void Renderer2D::BeginRender(Camera* camera)
{
	StartBatch();
	currentCam = camera;
	_data.textureShader->SetMat4("projection", currentCam->ViewMat());
}

void Renderer2D::EndRender()
{
	Flush();
}

void Renderer2D::Flush()
{
	if (_data.quadIndexCount == 0) 
		return; //Nothing to draw

	uint32_t dataSize = (uint32_t)((uint8_t*)_data.quadVertexBufferPtr - (uint8_t*)_data.quadVertexBufferBase);
	_data.quadVertexBuffer->SetData(_data.quadVertexBufferBase, dataSize);

	for (unsigned int i = 0; i < _data.textureSlotIndex; i++) {
		_data.textureSlots[i]->Bind(i);
	}

	_data.textureShader->BindShader();

	DrawIndexed(_data.quadVertexArray, _data.quadIndexCount);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	DrawQuad({ position.x, position.y, 0.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, color);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, Texture2D* texture, float tilingFactor, glm::vec4& tintColor)
{
	DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,  Texture2D* texture, float tilingFactor, glm::vec4& tintColor)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, texture, tilingFactor, tintColor);
}

void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID)
{
	constexpr size_t quadVertexCount = 4;
	const float textureIndex = 0.0f;
	constexpr glm::vec2 textureCoords[] = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f,1.0f},
		{0.0f, 1.0f}
	};

	const float tillingFactor = 0.0f;

	if (_data.quadIndexCount >= RendererData::maxIndices) {
		NextBatch();
	}

	for (size_t i = 0; i < quadVertexCount; i++) {
		_data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[i];
		_data.quadVertexBufferPtr->color = color;
		_data.quadVertexBufferPtr->texCoord = textureCoords[i];
		_data.quadVertexBufferPtr->tilingFactor = tillingFactor;
		_data.quadVertexBufferPtr->texIndex = textureIndex;
		_data.quadVertexBufferPtr->entityID = entityID;
		_data.quadVertexBufferPtr++;
	}

	_data.quadIndexCount += 6;
}

void Renderer2D::DrawQuad(const glm::mat4& transform, Texture2D* texture, float tilingFactor, glm::vec4& tintColor, int entityID)
{
	constexpr size_t quadVertexCount = 4;
	constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	tintColor.r = 1.0f;
	tintColor.g = 1.0f;

	if (_data.quadIndexCount >= RendererData::maxIndices)
		NextBatch();

	float textureIndex = 0.0f;
	for (uint32_t i = 1; i < _data.textureSlotIndex; i++)
	{
		if (_data.textureSlots[i] == texture)
		{
			textureIndex = (float)i;
			break;
		}
	}

	if (textureIndex == 0.0f)
	{
		if (_data.textureSlotIndex >= RendererData::maxTextureSlots)
			NextBatch();

		textureIndex = (float)_data.textureSlotIndex;
		_data.textureSlots[_data.textureSlotIndex] = texture;
		_data.textureSlotIndex++;
	}

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		_data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[i];
		_data.quadVertexBufferPtr->color = tintColor;
		_data.quadVertexBufferPtr->texCoord = textureCoords[i];
		_data.quadVertexBufferPtr->texIndex = textureIndex;
		_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		_data.quadVertexBufferPtr->entityID = entityID;
		_data.quadVertexBufferPtr++;
	}

	_data.quadIndexCount += 6;
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor)
{
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor)
{
}

void Renderer2D::DrawIndexed(const std::shared_ptr<VAO>& vertexArray, uint32_t indexCount)
{
	vertexArray->Bind();
	vertexArray->GetIndexBuffer()->Bind();
	uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer2D::StartBatch()
{
	_data.quadIndexCount = 0;
	_data.quadVertexBufferPtr = _data.quadVertexBufferBase;
	_data.textureSlotIndex = 1;
}

void Renderer2D::NextBatch()
{
	Flush();
	StartBatch();
}
