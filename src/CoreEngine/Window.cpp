#include <iostream>
#include "CoreEngine/Window.h"

using namespace std;

namespace window
{
	Window::Window(float width, float height, const char* windowName, GLFWmonitor* monitor, GLFWwindow* share)
	{
		this->width = width;
		this->height = height;
		this->windowName = windowName;
		this->monitor = monitor;
		this->share = share;
		initWindow();
	}

	Window::~Window()
	{
		closeWindow();
	}

	void Window::initWindow()
	{
		window = glfwCreateWindow(width, height, windowName, monitor, share);

		glfwMakeContextCurrent(window);
	}

	void Window::closeWindow()
	{
		glfwTerminate();
	}

	bool Window::windowShouldClose(GLFWwindow* window)
	{
		return glfwWindowShouldClose(window);
	}

	GLFWwindow* Window::getWindow()
	{
		return window;
	}

	float Window::getWidth()
	{
		return width;
	}

	float Window::getHeight()
	{
		return height;
	}
}