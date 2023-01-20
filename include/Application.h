#pragma once

#include "graphics/Display.h"
#include "graphics/Renderer.h"
#include "graphics/shader.h"
#include "graphics/ImGuiLayer.h"
#include "graphics/framebuffer.h"
#include "graphics/camera.h"

#include "core/Scene.h"

#include "panels/WorldPanel.h"

#include <memory>

namespace unicell
{
	class Application
	{
	private:
		Application();
	public:
		static Application* get();

		~Application();

		void Update();
	private:
		void RenderImGui();
	private:
		Scene* currentScene = nullptr;
		std::shared_ptr<WorldPanel> worldPanel;
	private:
		unsigned int vao, buffer;
		std::shared_ptr<Shader> shader;
	private:
		std::shared_ptr<Framebuffer> framebuffer;
		std::shared_ptr<ImGuiLayer> imguiLayer;
		std::shared_ptr<Display> display;
	private:
		static Application* instance;
	};
}