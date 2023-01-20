#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace unicell
{
	class Camera
	{
	public:
		static void CreateOrtho(float left,float right,float bottom,float top);
		static void move(const glm::vec3& movement);
		
		static glm::mat4 getViewMatrix();
		static glm::mat4 getProjectionMatrix();
	private:
		static glm::mat4 projection;
		static glm::vec3 position;
		static float rotation;
	};
}