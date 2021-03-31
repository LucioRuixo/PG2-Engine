#include "Camera.h"

Camera::Camera(Renderer* _renderer)
{
	renderer = _renderer;
}

Camera::~Camera() {}

void Camera::translate(float x, float y, float z)
{
	glm::mat4 translatedView = glm::translate(renderer->getView(), glm::vec3(-x, -y, -z));
	renderer->setView(renderer->getShaderProgram(), translatedView);
}

void Camera::translate(glm::vec3 translation)
{
	glm::mat4 translatedView = glm::translate(renderer->getView(), glm::vec3(-translation.x, -translation.y, -translation.z));
	renderer->setView(renderer->getShaderProgram(), translatedView);
}