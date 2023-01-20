#pragma once

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

namespace unicell
{
	class ImGuiLayer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void NewFrame();
		void Render();
	private:
	};
}