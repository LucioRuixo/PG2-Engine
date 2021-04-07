#include "Camera.h"

Camera::Camera(Renderer* _renderer)
{
	renderer = _renderer;

	transform = new Transform();
	//setPosition(0.0f, 0.0f, 0.0f);
}

Camera::~Camera() { if (transform) delete transform; }

void Camera::setTransformPosition(float x, float y, float z)
{
	transform->position = vec3(x, y, z);
}

void Camera::setPosition(float x, float y, float z)
{
	mat4 translatedView = glm::translate(renderer->getView(), vec3(-x, -y, -z));
	renderer->setView(renderer->getShaderProgram(), translatedView);

	setTransformPosition(x, y, z);
}

void Camera::setPosition(vec3 value)
{
	setPosition(value.x, value.y, value.z);
}

void Camera::translate(float x, float y, float z)
{
	float translationX = x - transform->position.x;
	float translationY = y - transform->position.y;
	float translationZ = z - transform->position.z;
	mat4 translatedView = glm::translate(renderer->getView(), vec3(translationX, translationY, translationZ));
	renderer->setView(renderer->getShaderProgram(), translatedView);

	float newTransformX = transform->position.x + x;
	float newTransformY = transform->position.y + y;
	float newTransformZ = transform->position.z + z;
	setTransformPosition(newTransformX, newTransformY, newTransformZ);
}

void Camera::translate(vec3 translation)
{
	translate(translation.x, translation.y, translation.z);
}