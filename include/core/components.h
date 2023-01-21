#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace unicell
{
	static int idCounter = 0;
	struct UnicellEntity
	{
		std::string name = "entity";
		int UID = idCounter++;
	};

	struct SpriteRenderer
	{
		glm::vec4 color = glm::vec4(1.0f);
	};

	struct TransformComponent
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);
		float rotation = 0.0f;
	};
}