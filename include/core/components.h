#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace unicell
{
	struct UnicellEntity
	{
		std::string name = "entity";
	};

	struct SpriteRenderer
	{
		glm::vec4 color = glm::vec4(1.0f);
	};

	struct TransformComponent
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(0.0f);
		float rotation = 0.0f;
	};
}