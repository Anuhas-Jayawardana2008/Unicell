#include "core/Scene.h"

namespace unicell
{
	Scene::Scene()
	{
		this->registry = entt::basic_registry();
		this->scriptEngine = std::make_shared<ScriptEngine>(this);
	}

	entt::entity Scene::CreateEntity()
	{
		entt::entity result = this->registry.create();
		
		this->registry.emplace<UnicellEntity>(result);
		this->registry.emplace<TransformComponent>(result);
		this->registry.emplace<SpriteRenderer>(result);
		auto& sc = this->registry.emplace<ScriptComponent>(result);
		sc.scriptPath = "assets/scripts/test.lua";

		return result;
	}

	// SCRIPTS
	void Scene::InitializeScripts()
	{
		this->scriptEngine->Initialize();
		this->scriptEngine->LoadEngineUtils();

		auto view = this->registry.view<ScriptComponent>();
		for (auto& entity : view)
		{
			auto& sc = this->registry.get<ScriptComponent>(entity);
			this->scriptEngine->RunFile(sc.scriptPath);
			this->scriptEngine->Start(entity);
		}
	}
	void Scene::UpdateScripts()
	{
		auto view = this->registry.view<ScriptComponent>();

		for (auto& entity : view)
		{
			auto& sc = this->registry.get<ScriptComponent>(entity);
			this->scriptEngine->RunFile(sc.scriptPath);
			this->scriptEngine->EditProperties(entity);
			this->scriptEngine->Update();
		}
	}
	// END - SCRIPTS

	void Scene::OnPlayCallback()
	{
		this->InitializeScripts();
	}

	void Scene::OnStopCallback()
	{
		this->scriptEngine->Close();
	}

	void Scene::OnRuntimeCallback()
	{
		this->UpdateScripts();
		this->selectedEntity = entt::null;
	}

	void Scene::Update()
	{
		auto view = this->registry.view<TransformComponent>();
		for (auto& entity : view)
		{
			auto& transform = this->registry.get<TransformComponent>(entity);
			auto& renderer = this->registry.get<SpriteRenderer>(entity);
			Renderer::DrawQuad(transform.position.x,transform.position.y,transform.scale.x,transform.scale.y,transform.rotation,renderer.color);
		}

		if (this->playing) this->OnRuntimeCallback();
	}
}