#pragma once

#include "core/components.h"
#include "graphics/Renderer.h"

#include <entt.hpp>

namespace unicell
{
	class Scene
	{
	public:
		Scene();
		
		entt::registry& GetRegistry();
		entt::entity CreateEntity();

		entt::entity& GetSelectedEntity();
		void SetSelectedEntity(const entt::entity& entity);

		// callbacks...
		void OnPlayCallback();
		void OnStopCallback();
		void OnRuntimeCallback();
		
		void setPlayState(bool state);
		bool getPlayState();

		void Update();
	private:
		bool playing = false;
		entt::registry registry;
		entt::entity selectedEntity{ entt::null };
	};
}