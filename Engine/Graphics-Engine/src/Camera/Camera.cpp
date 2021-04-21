#include "Camera.h"

Camera::Camera(Renderer* _renderer)
{
	forward = vec3(0.0f, 0.0f, -1.0f);
	upVector = vec3(0.0f, 1.0f, 0.0f);
	view = mat4(1.0f);

	renderer = _renderer;

	transform = new Transform();
	transform->setRotation(0.0f, -90.0f, 0.0f);
}

Camera::~Camera() { if (transform) delete transform; }

void Camera::updateViewMatrix()
{
	renderer->setView(view);
}

void Camera::setPosition(float x, float y, float z)
{
	transform->setPosition(x, y, z);

	view = lookAt(transform->getPosition(), transform->getPosition() + forward, upVector);
	updateViewMatrix();

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "viewPosition");
	glUniform3f(uniformLocation, transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);
}

void Camera::translate(float x, float y, float z)
{
	vec3 newPosition = transform->getPosition();

	vec3 right = normalize(cross(forward, upVector));
	vec3 up = cross(right, forward);
	newPosition += right * x + up * y - forward * z;

	setPosition(newPosition.x, newPosition.y, newPosition.z);
}

void Camera::setRotation(float pitch, float yaw, float roll)
{
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	transform->setRotation(pitch, yaw, roll);

	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(forward);

	view = lookAt(transform->getPosition(), transform->getPosition() + forward, upVector);
	updateViewMatrix();
}

void Camera::rotate(float pitch, float yaw, float roll)
{
	float newPitch = transform->getRotation().x + pitch;
	float newYaw = transform->getRotation().y + yaw;
	float newRoll = transform->getRotation().z + roll;

	setRotation(newPitch, newYaw, newRoll);
}