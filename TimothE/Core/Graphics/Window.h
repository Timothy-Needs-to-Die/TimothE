#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>

#include <glm.hpp>

#include "../Events/Event.h"

#include "../Events/ApplicationEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"

class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	static void Init(unsigned int width, unsigned int height, const char* name);

	//Gets the GLFWwindow associated with this Window class
	static GLFWwindow* GetGLFWWindow();

	static glm::vec2 GetWindowSize();
	static glm::vec2 GetHalfWindowSize();

	static float GetAspectRatio();

	//Sets an event callback for the window
	static void SetEventCallback(const EventCallbackFn& callback);

	//Sets the background colour of the window
	static void SetWindowColour(float r, float g, float b, float a);

	//Handles GLFW closing and termination behavior
	static void DestroyWindow();

	//Creates a GLFWwindow with the passed in width, height and name.
	static void CreateWindow();

	//Swaps the front and back buffers of the window
	static void SwapBuffers();

	static float GetHeight();
	static float GetWidth();

	static void ShowFPS(float dt);


	static void SetFullscreen(bool val);
private:


private:
	static GLFWwindow* _pWindow;

	struct WindowData
	{
		std::string _title;
		unsigned int _width, _height;
		bool _vsync;
		EventCallbackFn _eventCallback;
	};

	static WindowData _windowData;
};

