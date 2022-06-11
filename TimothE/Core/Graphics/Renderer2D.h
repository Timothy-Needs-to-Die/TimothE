#pragma once

#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "Shader.h"

#include "../../Quad.h"
#include "../../Camera.h"
#include "../../Texture2D.h"

struct QuadVertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
	int lightLevel;
	float texIndex;
	float tilingFactor;
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

class Renderer2D
{
public:
	static void Init();
	static void Shutdown();

	static void BeginRender(Camera* camera);
	static void EndRender();

	//Draw Quads

	/// <summary>
	/// Draws a Quad for use in the game world
	/// </summary>
	/// <param name="quad">The Render quad for the Object, contains size and position</param>
	/// <param name="texture">Texture to be displayed. If left as nullptr a white texture is used</param>
	/// <param name="lightLevel">Light level for tile depending on light sources. 5 is default.</param>
	/// <param name="uvCoordinates">UV Coordinates for the texutre. If left as nullptr standard tex coords for quads are used</param>
	/// <param name="tintColor">A tinting color for the object's texture. If left default this will be white</param>
	static void DrawQuad(const Quad& quad, Texture2D* texture, glm::vec2* uvCoordinates = nullptr, int lightLevel = 5,
		glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);

	/// <summary>
	/// Draws a Object for use in the game world
	/// </summary>
	/// <param name="transform">The transform for the Object, contains size and position</param>
	/// <param name="texture">Texture to be displayed. If left as nullptr a white texture is used</param>
	/// <param name="uvCoordinates">UV Coordinates for the texutre. If left as nullptr standard tex coords for quads are used</param>
	/// <param name="tintColor">A tinting color for the object's texture. If left default this will be white</param>
	/// <param name="lightLevel">Light level for tile depending on light sources. 5 is default.</param>
	static void DrawQuad(const glm::mat4& transform, Texture2D* texture, glm::vec2* uvCoordinates = nullptr,
		float tilingFactor = 1.0f, glm::vec4& tintColor = glm::vec4(1.0f), int lightLevel = 5);

	//Draw UI

	/// <summary>
	/// Draws a Quad for the UI
	/// </summary>
	/// <param name="quad">The Render quad for the UI Object, contains size and position</param>
	/// <param name="texture">Texture to be displayed. If left as nullptr a white texture is used</param>
	/// <param name="uvCoordinates">UV Coordinates for the texutre. If left as nullptr standard tex coords for quads are used</param>
	/// <param name="tintColor">A tinting color for the object's texture. If left default this will be white</param>
	static void DrawUIQuad(const Quad& quad, Texture2D* texture = nullptr, glm::vec2* uvCoordinates = nullptr,
		glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);

	/// <summary>
	/// Draws a Object for the UI
	/// </summary>
	/// <param name="transform">The transform for the UI Object, contains size and position</param>
	/// <param name="texture">Texture to be displayed. If left as nullptr a white texture is used</param>
	/// <param name="uvCoordinates">UV Coordinates for the texutre. If left as nullptr standard tex coords for quads are used</param>
	/// <param name="tintColor">A tinting color for the object's texture. If left default this will be white</param>
	static void DrawUIQuad(const glm::mat4& transform, Texture2D* texture, glm::vec2* uvCoordinates = nullptr,
		float tilingFactor = 1.0f, glm::vec4& tintColor = glm::vec4(1.0f));

	static struct RendererData GenerateRendererData();

	static void AddData(struct RendererData& data, const Quad& quad, Texture2D* texture, glm::vec2* uvCoordinates = nullptr,
		float tilingFactor = 1.0f, glm::vec4& tintColor = glm::vec4(1.0f));

	static void DrawIndexed(const std::shared_ptr<VAO>& vertexArray, uint32_t indexCount);
private:
	static void Flush();
	static void StartBatch();
	static void NextBatch();
};

