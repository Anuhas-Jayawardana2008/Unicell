#include "core/Scene.h"

namespace unicell
{
	Scene::Scene()
	{
		this->registry = entt::basic_registry();
	}

	entt::entity Scene::CreateEntity()
	{
		entt::entity result = this->registry.create();
		this->registry.emplace<UnicellEntity>(result);
		this->registry.emplace<TransformComponent>(result);
		this->registry.emplace<SpriteRenderer>(result);
		return result;
	}

	entt::registry& Scene::GetRegistry()
	{
		return this->registry;
	}

	entt::entity& Scene::GetSelectedEntity()
	{
		return this->selectedEntity;
	}
	
	void Scene::SetSelectedEntity(const entt::entity& entity)
	{
		this->selectedEntity = entity;
	}

	void Scene::setPlayState(bool state)
	{
		this->playing = state;
	}

	bool Scene::getPlayState()
	{
		return this->playing;
	}

	void Scene::OnPlayCallback()
	{

	}

	void Scene::OnStopCallback()
	{

	}

	void Scene::OnRuntimeCallback()
	{
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