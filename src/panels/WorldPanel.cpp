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

		if (ImGui::BeginPopupContextWindow("context_registry"))
		{
			if (ImGui::MenuItem("Create New Entity"))
			{
				this->context->CreateEntity();
			}
			ImGui::EndPopup();
		}
		
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImGui::BeginPopup("context_registry");
		}
		for (auto& entity : view)
		{
			auto& entityComponent = this->context->GetRegistry().get<UnicellEntity>(entity);
			if (ImGui::Button(entityComponent.name.c_str()))
			{
				this->context->SetSelectedEntity(entity);
			}
		}
		ImGui::End();
	}
}