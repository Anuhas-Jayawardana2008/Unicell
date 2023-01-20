#include "graphics/Display.h"

namespace unicell
{
	Display::Display()
	{
		glfwInit();

		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		this->window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
		glfwMakeContextCurrent(this->window);
		glfwSwapInterval(1);
		gladLoadGL();
	}

	Display::~Display()
	{
		glfwDestroyWindow(this->window);
		glfwTerminate();
	}

	bool Display::isRunning()
	{
		return !glfwWindowShouldClose(this->window);
	}

	void Display::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(this->window);
	}
}