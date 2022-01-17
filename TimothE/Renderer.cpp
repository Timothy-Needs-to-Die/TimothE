#include <GL/glew.h>
#include "Renderer.h"
#include "Texture2D.h"


//TEMP
static const GLfloat g_vertex_buffer_data[] =
{
	//pos				//tex
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	0.0f,  1.0f, 0.0f, 0.5f, 1.0f
};

void Renderer::Initialize()
{
	
}

void Renderer::RenderDrawables(vector<GameObject*> gameObjects)
{
	for (auto& obj : gameObjects)
	{
		Render(obj);
	}
}

void Renderer::Render(GameObject* gameObject)
{
	glUseProgram(gameObject->GetShaderID());
	
	//////////////////////////////////
	//NEEDS VERTICES FROM GAMEOBJECT//
	//////////////////////////////////

	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(float),                  // stride
		(void*)(3 * sizeof(float))            // array buffer offset
	);
	glEnableVertexAttribArray(1);

	glBindTexture(GL_TEXTURE_2D, gameObject->GetTextureID());
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
