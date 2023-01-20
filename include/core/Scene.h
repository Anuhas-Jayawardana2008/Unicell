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
		
		void Update();
	private:
		entt::registry registry;
	};
}