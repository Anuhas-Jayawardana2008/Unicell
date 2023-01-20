#include "graphics/camera.h"

namespace unicell
{
	glm::mat4 Camera::projection;
	glm::vec3 Camera::position;
	float Camera::rotation;

	void Camera::CreateOrtho(float left, float right, float bottom, float top)
	{
		projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}

	void Camera::move(const glm::vec3& movement)
	{
		position += movement;
	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		return projection;
	}

	glm::mat4 Camera::getViewMatrix()
	{
		return glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}