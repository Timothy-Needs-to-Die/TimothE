#include "../../pch.h"
#include "Renderer2D.h"
#include "OpenGLError.h"
#include "../../ResourceManager.h"


static RendererData _data;
static RendererData _uiData;

static Camera* currentCam;


void Renderer2D::Init()
{
	_data.quadVertexArray = VAO::Create();
	_uiData.quadVertexArray = VAO::Create();

	_data.quadVertexBuffer = VBO::Create(_data.maxVertices * sizeof(QuadVertex));
	_uiData.quadVertexBuffer = VBO::Create(_uiData.maxVertices * sizeof(QuadVertex));

	_data.quadVertexBuffer->SetLayout({
			{ ShaderDataTypes::Float3, "a_Position"     },
			{ ShaderDataTypes::Float4, "a_Color"        },
			{ ShaderDataTypes::Float2, "a_TexCoord"     },
			{ ShaderDataTypes::Int, "a_LightLevel"     },
			{ ShaderDataTypes::Float,  "a_TexIndex"     },
			{ ShaderDataTypes::Float,  "a_TilingFactor" },
			{ ShaderDataTypes::Int,  "a_EntityID" }
		});

	_uiData.quadVertexBuffer->SetLayout({
			{ ShaderDataTypes::Float3, "a_Position"     },
			{ ShaderDataTypes::Float4, "a_Color"        },
			{ ShaderDataTypes::Float2, "a_TexCoord"     },
			{ ShaderDataTypes::Int, "a_LightLevel"},
			{ ShaderDataTypes::Float,  "a_TexIndex"     },
			{ ShaderDataTypes::Float,  "a_TilingFactor" },
			{ ShaderDataTypes::Int,  "a_EntityID" }
		});

	_data.quadVertexArray->AddVertexBuffer(_data.quadVertexBuffer);
	_uiData.quadVertexArray->AddVertexBuffer(_uiData.quadVertexBuffer);

	_data.quadVertexBufferBase = new QuadVertex[_data.maxVertices];
	_uiData.quadVertexBufferBase = new QuadVertex[_uiData.maxVertices];

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
	std::shared_ptr<IBO> quadIB2 = IBO::Create(quadIndices, _uiData.maxIndices);

	_data.quadVertexArray->SetIndexBuffer(quadIB);
	_uiData.quadVertexArray->SetIndexBuffer(quadIB2);

	delete[] quadIndices;

	_data.whiteTexture = ResourceManager::GetTexture("whiteTexture.png");
	_uiData.whiteTexture = ResourceManager::GetTexture("whiteTexture.png");

	_data.textureShader = std::make_shared<Shader>("Resources/Shaders/vs_Texture.vert", "Resources/Shaders/fr_Texture.frag");
	_uiData.textureShader = std::make_shared<Shader>("Resources/Shaders/vr_UIShader.vert", "Resources/Shaders/fr_UIShader.frag");

	_data.textureSlots[0] = _data.whiteTexture;
	_uiData.textureSlots[0] = _uiData.whiteTexture;

	_data.quadVertexPositions[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
	_data.quadVertexPositions[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
	_data.quadVertexPositions[2] = { 1.0f,  1.0f, 0.0f, 1.0f };
	_data.quadVertexPositions[3] = { 0.0f,  1.0f, 0.0f, 1.0f };


	_uiData.quadVertexPositions[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
	_uiData.quadVertexPositions[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
	_uiData.quadVertexPositions[2] = { 1.0f,  1.0f, 0.0f, 1.0f };
	_uiData.quadVertexPositions[3] = { 0.0f,  1.0f, 0.0f, 1.0f };
}

void Renderer2D::Shutdown()
{

}

void Renderer2D::BeginRender(Camera* camera)
{
	StartBatch();
	currentCam = camera;
	_data.textureShader->SetMat4("view", currentCam->ViewProj());

	_data.quadIndexCount = 0;
	_data.quadVertexBufferPtr = _data.quadVertexBufferBase;
	_data.textureSlotIndex = 1;

	_uiData.quadIndexCount = 0;
	_uiData.quadVertexBufferPtr = _uiData.quadVertexBufferBase;
	_uiData.textureSlotIndex = 1;
}

void Renderer2D::EndRender()
{
	Flush();
}

void Renderer2D::Flush()
{
	if (_data.quadIndexCount != 0) {
		uint32_t dataSize = (uint32_t)((uint8_t*)_data.quadVertexBufferPtr - (uint8_t*)_data.quadVertexBufferBase);
		_data.quadVertexBuffer->SetData(_data.quadVertexBufferBase, dataSize);

		for (unsigned int i = 0; i < _data.textureSlotIndex; i++) {
			_data.textureSlots[i]->Bind(i);
		}

		_data.textureShader->BindShader();

		DrawIndexed(_data.quadVertexArray, _data.quadIndexCount);
	}

	if (_uiData.quadIndexCount != 0) {
		uint32_t dataSize = (uint32_t)((uint8_t*)_uiData.quadVertexBufferPtr - (uint8_t*)_uiData.quadVertexBufferBase);
		_uiData.quadVertexBuffer->SetData(_uiData.quadVertexBufferBase, dataSize);

		for (unsigned int i = 0; i < _uiData.textureSlotIndex; i++) {
			_uiData.textureSlots[i]->Bind(i);
		}

		_uiData.textureShader->BindShader();

		DrawIndexed(_uiData.quadVertexArray, _uiData.quadIndexCount);
	}
}

void Renderer2D::DrawUIQuad(const glm::mat4& transform, Texture2D* texture, glm::vec2* uvCoordinates /*= nullptr*/, float tilingFactor /*= 1.0f*/, glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
{
	constexpr size_t quadVertexCount = 4;
	glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	if (uvCoordinates != nullptr) {
		textureCoords[0] = uvCoordinates[0];
		textureCoords[1] = uvCoordinates[1];
		textureCoords[2] = uvCoordinates[2];
		textureCoords[3] = uvCoordinates[3];
	}

	if (_uiData.quadIndexCount >= RendererData::maxIndices)
		NextBatch();

	float textureIndex = -1.0f;
	if (texture == nullptr) {
		textureIndex = 0.0f;
	}
	else {
		for (uint32_t i = 1; i < _uiData.textureSlotIndex; i++)
		{
			if (_uiData.textureSlots[i] == texture)
			{
				textureIndex = (float)i;
				break;
			}
		}
	}

	if (textureIndex == -1.0f)
	{
		textureIndex = (float)_uiData.textureSlotIndex;
		_uiData.textureSlots[_uiData.textureSlotIndex] = texture;
		_uiData.textureSlotIndex++;
	}

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		_uiData.quadVertexBufferPtr->position = transform * _uiData.quadVertexPositions[i];
		_uiData.quadVertexBufferPtr->color = tintColor;
		_uiData.quadVertexBufferPtr->texCoord = textureCoords[i];
		_uiData.quadVertexBufferPtr->texIndex = textureIndex;
		_uiData.quadVertexBufferPtr->tilingFactor = tilingFactor;
		_uiData.quadVertexBufferPtr->lightLevel = 5;
		_uiData.quadVertexBufferPtr++;
	}

	_uiData.quadIndexCount += 6;
}

struct RendererData Renderer2D::GenerateRendererData()
{
	RendererData data;

	data.quadVertexArray = VAO::Create();

	data.quadVertexBuffer = VBO::Create(data.maxVertices * sizeof(QuadVertex));

	data.quadVertexBuffer->SetLayout({
			{ ShaderDataTypes::Float3, "a_Position"     },
			{ ShaderDataTypes::Float4, "a_Color"        },
			{ ShaderDataTypes::Float2, "a_TexCoord"     },
			{ ShaderDataTypes::Int, "a_LightLevel"     },
			{ ShaderDataTypes::Float,  "a_TexIndex"     },
			{ ShaderDataTypes::Float,  "a_TilingFactor" },
			{ ShaderDataTypes::Int,  "a_EntityID" }
		});

	data.quadVertexArray->AddVertexBuffer(data.quadVertexBuffer);

	data.quadVertexBufferBase = new QuadVertex[data.maxVertices];

	unsigned int* quadIndices = new unsigned int[data.maxIndices];

	unsigned int offset = 0;
	for (unsigned int i = 0; i < data.maxIndices; i += 6) {
		quadIndices[i + 0] = offset + 0;
		quadIndices[i + 1] = offset + 1;
		quadIndices[i + 2] = offset + 2;

		quadIndices[i + 3] = offset + 2;
		quadIndices[i + 4] = offset + 3;
		quadIndices[i + 5] = offset + 0;

		offset += 4;
	}

	std::shared_ptr<IBO> quadIB = IBO::Create(quadIndices, data.maxIndices);

	data.quadVertexArray->SetIndexBuffer(quadIB);
	delete[] quadIndices;

	data.whiteTexture = ResourceManager::GetTexture("whiteTexture.png");

	unsigned int samplers[data.maxTextureSlots];
	for (unsigned int i = 0; i < data.maxTextureSlots; i++) {
		samplers[i] = i;
	}

	data.textureShader = std::make_shared<Shader>("Resources/Shaders/vs_Texture.vert", "Resources/Shaders/fr_Texture.frag");

	data.textureSlots[0] = data.whiteTexture;

	data.quadVertexPositions[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
	data.quadVertexPositions[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
	data.quadVertexPositions[2] = { 1.0f,  1.0f, 0.0f, 1.0f };
	data.quadVertexPositions[3] = { 0.0f,  1.0f, 0.0f, 1.0f };

	data.quadVertexBufferPtr = data.quadVertexBufferBase;
	data.quadIndexCount = 0;

	return data;
}

void Renderer2D::AddData(RendererData& data, const Quad& quad, Texture2D* texture, glm::vec2* uvCoordinates /*= nullptr*/, float tilingFactor /*= 1.0f*/, glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(quad.position, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(quad.size, 1.0f));

	constexpr size_t quadVertexCount = 4;
	glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	if (uvCoordinates != nullptr) {
		textureCoords[0] = uvCoordinates[0];
		textureCoords[1] = uvCoordinates[1];
		textureCoords[2] = uvCoordinates[2];
		textureCoords[3] = uvCoordinates[3];
	}

	float textureIndex = -1.0f;
	if (texture == nullptr) {
		textureIndex = 0.0f;
	}
	else {
		for (uint32_t i = 1; i < data.textureSlotIndex; i++)
		{
			if (data.textureSlots[i] == texture)
			{
				textureIndex = (float)i;
				break;
			}
		}
	}

	if (textureIndex == -1.0f)
	{
		textureIndex = (float)data.textureSlotIndex;
		data.textureSlots[data.textureSlotIndex] = texture;
		data.textureSlotIndex++;
	}

	for (int i = 0; i < 4; ++i) {
		data.quadVertexBufferPtr->position = transform * data.quadVertexPositions[i];
		data.quadVertexBufferPtr->color = tintColor;
		data.quadVertexBufferPtr->texCoord = textureCoords[i];
		data.quadVertexBufferPtr->lightLevel = 5;
		data.quadVertexBufferPtr->texIndex = textureIndex;
		data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		data.quadVertexBufferPtr++;
	}

	data.quadIndexCount += 6;
}

void Renderer2D::DrawUIQuad(const Quad& quad, Texture2D* texture /*= nullptr*/, glm::vec2* uvCoordinates /*= nullptr*/, glm::vec4& tintColor /*= glm::vec4(1.0f)*/, float tilingFactor /*= 1.0f*/)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(quad.position, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(quad.size, 1.0f));
	DrawUIQuad(transform, texture, uvCoordinates, tilingFactor, tintColor);
}



void Renderer2D::DrawQuad(const glm::mat4& transform, Texture2D* texture, glm::vec2* uvCoordinates, float tilingFactor, glm::vec4& tintColor, int lightLevel /*= 5*/)
{
	constexpr size_t quadVertexCount = 4;
	glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	if (uvCoordinates != nullptr) {
		textureCoords[0] = uvCoordinates[0];
		textureCoords[1] = uvCoordinates[1];
		textureCoords[2] = uvCoordinates[2];
		textureCoords[3] = uvCoordinates[3];
	}

	if (_data.quadIndexCount >= RendererData::maxIndices)
		NextBatch();

	float textureIndex = -1.0f;
	if (texture == nullptr) {
		textureIndex = 0.0f;
	}
	else {
		for (uint32_t i = 1; i < _data.textureSlotIndex; i++)
		{
			if (_data.textureSlots[i] == texture)
			{
				textureIndex = (float)i;
				break;
			}
		}
	}

	if (textureIndex == -1.0f)
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
		_data.quadVertexBufferPtr->lightLevel = lightLevel;
		_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		_data.quadVertexBufferPtr++;
	}

	_data.quadIndexCount += 6;
}

void Renderer2D::DrawQuad(const Quad& quad, Texture2D* texture, glm::vec2* uvCoordinates /* = nullptr */, int lightLevel /*= 5*/, glm::vec4& tintColor /*= glm::vec4(1.0f)*/, float tilingFactor /*= 1.0f*/)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(quad.position, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(quad.rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3(quad.size, 1.0f));
	DrawQuad(transform, texture, uvCoordinates, tilingFactor, tintColor, lightLevel);
}

void Renderer2D::DrawIndexed(const std::shared_ptr<VAO>& vertexArray, uint32_t indexCount)
{
	vertexArray->Bind();
	vertexArray->GetIndexBuffer()->Bind();
	uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
	GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Renderer2D::StartBatch()
{
	_data.quadIndexCount = 0;
	_data.quadVertexBufferPtr = _data.quadVertexBufferBase;
	_data.textureSlotIndex = 1;

	_uiData.quadIndexCount = 0;
	_uiData.quadVertexBufferPtr = _uiData.quadVertexBufferBase;
	_uiData.textureSlotIndex = 1;
}

void Renderer2D::NextBatch()
{
	Flush();
	StartBatch();
}
