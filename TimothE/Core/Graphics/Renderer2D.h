#pragma once

#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "Shader.h"

#include "../../Quad.h"
#include "../../Camera.h"
#include "../../Texture2D.h"

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
	/// <param name="uvCoordinates">UV Coordinates for the texutre. If left as nullptr standard tex coords for quads are used</param>
	/// <param name="tintColor">A tinting color for the object's texture. If left default this will be white</param>
	static void DrawQuad(const Quad& quad, Texture2D* texture, glm::vec2* uvCoordinates = nullptr,
		glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);

	/// <summary>
	/// Draws a Object for use in the game world
	/// </summary>
	/// <param name="transform">The transform for the Object, contains size and position</param>
	/// <param name="texture">Texture to be displayed. If left as nullptr a white texture is used</param>
	/// <param name="uvCoordinates">UV Coordinates for the texutre. If left as nullptr standard tex coords for quads are used</param>
	/// <param name="tintColor">A tinting color for the object's texture. If left default this will be white</param>
	static void DrawQuad(const glm::mat4& transform, Texture2D* texture, glm::vec2* uvCoordinates = nullptr,
		float tilingFactor = 1.0f, glm::vec4& tintColor = glm::vec4(1.0f));

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

private:
	static void Flush();
	static void DrawIndexed(const std::shared_ptr<VAO>& vertexArray, uint32_t indexCount);
	static void StartBatch();
	static void NextBatch();
};

