#include "CameraTransform.h"

CameraTransform::CameraTransform(Renderer* _renderer) : Transform()
{
	forward = vec3(0.0f, 0.0f, -1.0f);
	upVector = vec3(0.0f, 1.0f, 0.0f);
	view = mat4(1.0f);

	renderer = _renderer;
}

CameraTransform::~CameraTransform() {}

void CameraTransform::updateView()
{
	renderer->setView(view);
}

void CameraTransform::setPosition(float x, float y, float z)
{
	transformData.position.x = x;
	transformData.position.y = y;
	transformData.position.z = z;

	view = lookAt(transformData.position, transformData.position + forward, upVector);
	updateView();

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "viewPosition");
	glUniform3f(uniformLocation, transformData.position.x, transformData.position.y, transformData.position.z);
}

void CameraTransform::translate(float x, float y, float z)
{
	vec3 newPosition = transformData.position;

	vec3 right = normalize(cross(forward, upVector));
	vec3 up = cross(right, forward);
	newPosition += right * x + up * y - forward * z;

	setPosition(newPosition.x, newPosition.y, newPosition.z);
}

void CameraTransform::setRotation(float pitch, float yaw, float roll)
{
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	transformData.rotation.x = pitch;
	transformData.rotation.y = yaw;
	transformData.rotation.z = roll;

	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(forward);

	view = lookAt(transformData.position, transformData.position + forward, upVector);
	updateView();
}

void CameraTransform::rotate(float pitch, float yaw, float roll)
{
	float newPitch = transformData.rotation.x + pitch;
	float newYaw = transformData.rotation.y + yaw;
	float newRoll = transformData.rotation.z + roll;

	setRotation(newPitch, newYaw, newRoll);
}

void CameraTransform::setScale(float x, float y, float z) { cout << "Can not scale camera transform" << endl; }