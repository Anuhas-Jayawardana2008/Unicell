#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace unicell
{
	class Display
	{
	public:
		Display();
		~Display();

		bool isRunning();
		void Update();
	private:
		GLFWwindow* window;
	};
}