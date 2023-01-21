#pragma once

#include "core/Scene.h"
#include "graphics/Texture.h"

#include "imgui.h"
#include <memory>

namespace unicell
{
	class Toolbar
	{
	public:
		Toolbar(Scene* scene);
		~Toolbar();

		void Update();
	private:
		std::shared_ptr<Texture> playButtonCurrentState;
		std::shared_ptr<Texture> playIcon;
		std::shared_ptr<Texture> stopIcon;

		Scene* context;
	};
}