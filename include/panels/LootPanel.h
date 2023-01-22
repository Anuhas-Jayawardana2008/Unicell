#pragma once

#include "core/Scene.h"

#include "imgui.h"
#include <filesystem>

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
		void AttachScriptToEntity(const entt::entity& entity);
	private:
		Scene* context = nullptr;
	};
}