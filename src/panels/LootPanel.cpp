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

		if (context->GetRegistry().try_get<ScriptComponent>(entity) != nullptr)
		{
			if (ImGui::TreeNode("Script Component"))
			{
				auto& sc = context->GetRegistry().get<ScriptComponent>(entity);
				ImGui::InputText("script", (char*)sc.scriptPath.c_str(), 100,ImGuiInputTextFlags_ReadOnly);

				if (ImGui::Button("Remove Component"))
					context->GetRegistry().remove<ScriptComponent>(entity);
				ImGui::TreePop();
			}
		}

		if (context->GetRegistry().try_get<PhysicsComponent>(entity) != nullptr)
		{
			if (ImGui::TreeNode("Physics Component"))
			{
				ImGui::Checkbox("dynamic", &context->GetRegistry().get<PhysicsComponent>(entity).isDynamic);
				ImGui::DragFloat("friction", &context->GetRegistry().get<PhysicsComponent>(entity).friction);
				ImGui::DragFloat("density", &context->GetRegistry().get<PhysicsComponent>(entity).density);
				ImGui::DragFloat("restitution", &context->GetRegistry().get<PhysicsComponent>(entity).restitution);
				ImGui::DragFloat("restitution threshold", &context->GetRegistry().get<PhysicsComponent>(entity).restitutionThreshold);
				if (ImGui::Button("Remove Component"))
					context->GetRegistry().remove<PhysicsComponent>(entity);
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

		if (ImGui::BeginPopupModal("Add new script"))
		{
			std::string buffer;
			ImGui::InputText("script", (char*)buffer.c_str(), buffer.length() + 10);
			if (ImGui::Button("Add"))
			{
				auto& sc = this->context->GetRegistry().emplace_or_replace<ScriptComponent>(this->context->GetSelectedEntity());
				sc.scriptPath = "assets/scripts/" + buffer;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
				ImGui::CloseCurrentPopup();

			ImGui::EndPopup();
		}

		if (ImGui::BeginPopupModal("Add new component"))
		{
			if (ImGui::Button("Physics Component"))
			{
				this->context->GetRegistry().emplace_or_replace<PhysicsComponent>(this->context->GetSelectedEntity());
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Script"))
			{
				ImGui::CloseCurrentPopup();
				ImGui::OpenPopup("Add new script");
			}

			ImGui::EndPopup();
		}

		

		if (this->context->GetSelectedEntity() != entt::null)
		{
			DrawComponents(this->context->GetSelectedEntity());
			if (ImGui::Button("Add Component"))
			{
				ImGui::OpenPopup("Add new component");
			}
		}

		ImGui::End();
	}
}