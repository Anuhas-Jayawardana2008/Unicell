#pragma once

#include "core/components.h"
#include "core/ScriptEngine.h"
#include "graphics/Renderer.h"

#include <entt.hpp>
#include <box2D/box2d.h>
#include <vector>

namespace unicell
{
	class Scene
	{
	public:
		Scene();
		
		entt::registry& GetRegistry() { return this->registry; }
		entt::entity CreateEntity();

		entt::entity& GetSelectedEntity() { return this->selectedEntity; }
		void SetSelectedEntity(const entt::entity& entity) { this->selectedEntity = entity; }

		// callbacks...
		void OnPlayCallback();
		void OnStopCallback();
		void OnRuntimeCallback();
		
		void setPlayState(bool state) { this->playing = state; }
		bool getPlayState() { return this->playing; }

		void Update();
	private:
		std::shared_ptr<ScriptEngine> scriptEngine;
		void InitializeScripts();
		void UpdateScripts();
	private:
		bool playing = false;
		entt::registry registry;
		entt::entity selectedEntity{ entt::null };
	};
}