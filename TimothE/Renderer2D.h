#pragma once

#include "pch.h"
#include "Camera.h"
#include "Texture2D.h"
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "Shader.h"
#include "Quad.h"

class Renderer2D
{
public:
	static void Init();
	static void Shutdown();

	static void BeginRender(Camera* camera);
	static void EndRender();

	//Draw Quads
	static void DrawQuad(const Quad& quad, Texture2D* texture, glm::vec2* uvCoordinates = nullptr, glm::vec4 & tintColor = glm::vec4(1.0f),
		float tilingFactor = 1.0f);

	static void DrawQuad(const glm::mat4& transform, Texture2D* texture, glm::vec2* uvCoordinates = nullptr,
		float tilingFactor = 1.0f, glm::vec4& tintColor = glm::vec4(1.0f));

	//Draw UI
	static void DrawUIQuad(const Quad& quad, Texture2D* texture = nullptr, glm::vec2* uvCoordinates = nullptr, glm::vec4& tintColor = glm::vec4(1.0f),
		float tilingFactor = 1.0f);

	static void DrawUIQuad(const glm::mat4& transform, Texture2D* texture, glm::vec2* uvCoordinates = nullptr, 
		float tilingFactor = 1.0f, glm::vec4& tintColor = glm::vec4(1.0f));

private:
	static void Flush();
	static void DrawIndexed(const std::shared_ptr<VAO>& vertexArray, uint32_t indexCount);
	static void StartBatch();
	static void NextBatch();
};

