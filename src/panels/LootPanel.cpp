#include "panels/LootPanel.h"

namespace unicell
{
	void LootPanel::DrawComponents(entt::entity& entity)
	{
		ImGui::InputText("name", (char*)context->GetRegistry().get<UnicellEntity>(entity).name.c_str(), context->GetRegistry().get<UnicellEntity>(entity).name.length() + 10);
		if (context->GetRegistry().try_get<TransformComponent>(entity) != nullptr)
		{
			if (ImGui::TreeNode("Transform"))
			{
				ImGui::DragFloat3("position", glm::value_ptr(context->GetRegistry().get<TransformComponent>(entity).position), 0.009f);
				ImGui::DragFloat("rotation",&context->GetRegistry().get<TransformComponent>(entity).rotation);
				ImGui::DragFloat3("scale", glm::value_ptr(context->GetRegistry().get<TransformComponent>(entity).scale), 0.009f);
				ImGui::TreePop();
			}
		}

		if (context->GetRegistry().try_get<SpriteRenderer>(entity) != nullptr)
		{
			if (ImGui::TreeNode("Sprite Renderer"))
			{
				ImGui::ColorEdit4("color", glm::value_ptr(context->GetRegistry().get<SpriteRenderer>(entity).color));
				ImGui::TreePop();
			}
		}
	}

	LootPanel::LootPanel(Scene* scene)
		:context(scene)
	{

	}

	LootPanel::~LootPanel()
	{
		this->context = nullptr;
	}

	void LootPanel::Update()
	{
		ImGui::Begin("Loot");

		if (this->context->GetSelectedEntity() != entt::null)
			DrawComponents(this->context->GetSelectedEntity());
		ImGui::End();
	}
}