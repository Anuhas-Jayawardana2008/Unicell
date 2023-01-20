#include "Application.h"

namespace unicell
{
	Application* Application::instance = nullptr;
	entt::entity player = entt::null;

	Application* Application::get()
	{
		if (instance == nullptr)
		{
			instance = new Application();
			return instance;
		}
		else {
			return instance;
		}
	}

	Application::Application()
	{
		this->display = std::make_shared<Display>();
		this->imguiLayer = std::make_shared<ImGuiLayer>();
		this->framebuffer = std::make_shared<Framebuffer>();

		this->currentScene = new Scene();
		this->worldPanel = std::make_shared<WorldPanel>(currentScene);

		player = this->currentScene->CreateEntity();

		Camera::CreateOrtho(-1.0f, 1.0f, -1.0f, 1.0f);
	}

	Application::~Application()
	{
		delete this->currentScene;
	}

	void Application::RenderImGui()
	{
		ImGui::Begin("Viewport");
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		ImGui::Image((ImTextureID)this->framebuffer->getTextureID(), { viewportSize.x,viewportSize.y }, { 1,1 }, { 0,0 });
		ImGui::End();

		this->worldPanel->Update();
	}

	void Application::Update()
	{
		while (this->display->isRunning())
		{
			this->imguiLayer->NewFrame();
			this->RenderImGui();

			this->framebuffer->Bind();
			Renderer::Clear();
			this->currentScene->Update();
			this->framebuffer->Unbind();

			this->imguiLayer->Render();
			this->display->Update();
		}
	}
}