#include "panels/Toolbar.h"

namespace unicell
{
	Toolbar::Toolbar(Scene* scene)
		:context(scene)
	{
		this->playIcon = std::make_shared<Texture>("res/playIcon.png");
		this->stopIcon = std::make_shared<Texture>("res/stopIcon.png");
		this->playButtonCurrentState = this->playIcon;
	}

	Toolbar::~Toolbar()
	{
		this->context = nullptr;
	}

	void Toolbar::Update()
	{
		ImGui::Begin("##toolbar");
		if (ImGui::ImageButton((ImTextureID)this->playButtonCurrentState->getTextureID(), { 15.0f,15.0f }))
		{
			bool state = !this->context->getPlayState();
			
			if (state == false) this->context->OnStopCallback();
			if (state == true) this->context->OnPlayCallback();

			this->context->setPlayState(state);
			if (state == true) this->playButtonCurrentState = this->stopIcon;
			if (state == false) this->playButtonCurrentState = this->playIcon;
		}

		ImGui::End();
	}
}