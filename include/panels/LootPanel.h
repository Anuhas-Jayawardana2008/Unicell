#pragma once

#include "core/Scene.h"

#include "imgui.h"

namespace unicell
{
	class LootPanel
	{
	public:
		LootPanel(Scene* scene);
		~LootPanel();

		void DrawComponents(entt::entity& entity);
		void Update();
	private:
		Scene* context = nullptr;
	};
}