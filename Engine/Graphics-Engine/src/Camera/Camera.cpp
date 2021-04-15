#include "Camera.h"

Camera::Camera(Renderer* _renderer)
{
	direction = vec3(0.0f, 0.0f, -1.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	view = mat4(1.0f);

	renderer = _renderer;

	transform = new Transform();
	transform->rotation.y = -90.0f;
}

Camera::~Camera() { if (transform) delete transform; }

void Camera::updateViewMatrix()
{
	renderer->setView(renderer->getShaderProgram(), view);
}

void Camera::setPosition(float x, float y, float z)
{
	transform->position = vec3(x, y, z);

	view = lookAt(transform->position, transform->position + direction, up);
	updateViewMatrix();

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "viewPosition");
	glUniform3f(uniformLocation, transform->position.x, transform->position.y, transform->position.z);
}

void Camera::translate(float x, float y, float z)
{
	float newX = transform->position.x + x;
	float newY = transform->position.y + y;
	float newZ = transform->position.z + z;

	setPosition(newX, newY, newZ);
}

void Camera::setRotation(float pitch, float yaw, float roll)
{
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	transform->rotation = vec3(pitch, yaw, roll);

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);

	view = lookAt(transform->position, transform->position + direction, up);
	updateViewMatrix();
}

void Camera::rotate(float pitch, float yaw, float roll)
{
	float newPitch = transform->rotation.x + pitch;
	float newYaw = transform->rotation.y + yaw;
	float newRoll = transform->rotation.z + roll;

	setRotation(newPitch, newYaw, newRoll);
}