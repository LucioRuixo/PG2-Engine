#include "Camera.h"

Camera::Camera(Renderer* _renderer)
{
	forward = vec3(0.0f, 0.0f, -1.0f);
	upVector = vec3(0.0f, 1.0f, 0.0f);
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

	view = lookAt(transform->position, transform->position + forward, upVector);
	updateViewMatrix();

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "viewPosition");
	glUniform3f(uniformLocation, transform->position.x, transform->position.y, transform->position.z);
}

void Camera::translate(float x, float y, float z)
{
	vec3 newPosition = transform->position;

	vec3 right = normalize(cross(forward, upVector));
	vec3 up = cross(right, forward);
	newPosition += right * x + up * y - forward * z;

	setPosition(newPosition.x, newPosition.y, newPosition.z);
}

void Camera::setRotation(float pitch, float yaw, float roll)
{
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	transform->rotation = vec3(pitch, yaw, roll);

	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(forward);

	view = lookAt(transform->position, transform->position + forward, upVector);
	updateViewMatrix();
}

void Camera::rotate(float pitch, float yaw, float roll)
{
	float newPitch = transform->rotation.x + pitch;
	float newYaw = transform->rotation.y + yaw;
	float newRoll = transform->rotation.z + roll;

	setRotation(newPitch, newYaw, newRoll);
}