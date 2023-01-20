#include "panels/WorldPanel.h"

namespace unicell
{
	WorldPanel::WorldPanel(Scene* scene)
		:context(scene)
	{
	}

	WorldPanel::~WorldPanel()
	{
		this->context = nullptr;
	}

	void WorldPanel::Update()
	{
		auto view = this->context->GetRegistry().view<TransformComponent>();

		ImGui::Begin("World");
		for (auto& entity : view)
		{
			ImGui::Button("Entity");
		}
		ImGui::End();
	}
}