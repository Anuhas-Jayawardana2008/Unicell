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

		auto entities = this->context->GetRegistry().view<TransformComponent>();

		ImGuiTreeNodeFlags baseFlag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		for (auto& entity : entities)
		{
			auto& crntIdentifierComponent = this->context->GetRegistry().get<UnicellEntity>(entity);

			ImGuiTreeNodeFlags flags = baseFlag;
			if (this->context->GetSelectedEntity() != entt::null)
			{
				flags = (this->context->GetRegistry().get<UnicellEntity>(this->context->GetSelectedEntity()).UID == crntIdentifierComponent.UID) ? ImGuiTreeNodeFlags_Selected : 0 | baseFlag;
			}

			ImGui::PushID(crntIdentifierComponent.UID);

			bool treeNodeOpen = ImGui::TreeNodeEx(
				crntIdentifierComponent.name.c_str(),
				flags
			);
			ImGui::PopID();

			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
			{
				this->context->SetSelectedEntity(entity);
			}

			if (treeNodeOpen)
			{
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}
}