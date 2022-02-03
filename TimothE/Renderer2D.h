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
	static void Flush();

	//Draw Quads
	static void DrawQuad(const Quad& quad, const glm::vec4& color);
	static void DrawQuad(const Quad& quad, Texture2D* texture, glm::vec2* uvCoordinates = nullptr);
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Texture2D* texture, glm::vec2* uvCoordinates = nullptr, float tilingFactor = 1.0f,  glm::vec4& tintColor = glm::vec4(1.0f));
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Texture2D* texture, glm::vec2* uvCoordinates = nullptr, float tilingFactor = 1.0f,  glm::vec4& tintColor = glm::vec4(1.0f));

	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, glm::vec2* uvCoordinates = nullptr, int entityID = -1);
	static void DrawQuad(const glm::mat4& transform, Texture2D* texture, glm::vec2* uvCoordinates = nullptr, float tilingFactor = 1.0f, glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);

	//TODO: Implement these.
	static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Texture2D* texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Texture2D* texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

	static void DrawIndexed(const std::shared_ptr<VAO>& vertexArray, uint32_t indexCount);

private:
	static void StartBatch();
	static void NextBatch();
};

