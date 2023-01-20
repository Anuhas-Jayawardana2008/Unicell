#pragma once

#include "core/Scene.h"

#include "imgui.h"

namespace unicell
{
	class WorldPanel
	{
	public:
		WorldPanel(Scene* scene);
		~WorldPanel();

		void Update();
	private:
		Scene* context = nullptr;
	};
}