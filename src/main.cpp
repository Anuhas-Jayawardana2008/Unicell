#include "Application.h"

int main(void)
{
	unicell::Application* editor = unicell::Application::get();
	editor->Update();
	delete editor;

	return 0;
}