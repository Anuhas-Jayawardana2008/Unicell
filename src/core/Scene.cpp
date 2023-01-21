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
		this->registry.emplace<PhysicsComponent>(result);

		return result;
	}

	void Scene::CreatePhysicsWorld()
	{
		this->physicsWorld = std::make_shared<b2World>(b2Vec2(0.0f, -0.009f));

		auto view = this->registry.view<PhysicsComponent>();

		for (auto& entity : view)
		{
			auto& transform = this->registry.get<TransformComponent>(entity);
			auto& pc = this->registry.get<PhysicsComponent>(entity);
			
			b2BodyDef bodyDef;
			if (pc.isDynamic) bodyDef.type = b2_dynamicBody;
			if (!pc.isDynamic) bodyDef.type = b2_staticBody;
			bodyDef.position = b2Vec2(transform.position.x,transform.position.y);

			b2PolygonShape shape;
			shape.SetAsBox(transform.scale.x / 2,transform.scale.y / 2);

			b2FixtureDef fixtureDef;
			fixtureDef.density = pc.density;
			fixtureDef.shape = &shape;
			fixtureDef.friction = pc.friction;
			fixtureDef.restitution = pc.restitution;
			fixtureDef.restitutionThreshold = pc.restitutionThreshold;

			b2Body* body = this->physicsWorld->CreateBody(&bodyDef);
			pc.body = body;
			body->CreateFixture(&fixtureDef);
		}
	}

	void Scene::UpdatePhysicsWorld()
	{
		this->physicsWorld->Step(3.0f, 6, 2);
		auto view = this->registry.view<PhysicsComponent>();

		for (auto& entity : view)
		{
			auto& transform = this->registry.get<TransformComponent>(entity);
			auto& pc = this->registry.get<PhysicsComponent>(entity);
			
			transform.position.x = pc.body->GetPosition().x;
			transform.position.y = pc.body->GetPosition().y;
			transform.rotation = pc.body->GetAngle();
		}
	}

	void Scene::OnPlayCallback()
	{
		this->CreatePhysicsWorld();
	}

	void Scene::OnStopCallback()
	{
	}

	void Scene::OnRuntimeCallback()
	{
		this->selectedEntity = entt::null;
		this->UpdatePhysicsWorld();
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