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

	void Scene::Update()
	{
		auto view = this->registry.view<TransformComponent>();
		for (auto& entity : view)
		{
			auto& transform = this->registry.get<TransformComponent>(entity);
			auto& renderer = this->registry.get<SpriteRenderer>(entity);
			Renderer::DrawQuad(transform.position.x, transform.position.y, transform.scale.x, transform.scale.y);
		}
	}
}