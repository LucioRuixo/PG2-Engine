#include "CameraTransform.h"

CameraTransform::CameraTransform(Renderer* _renderer) : Transform()
{
	forward = vec3(0.0f, 0.0f, -1.0f);
	view = mat4(1.0f);

	renderer = _renderer;
}

CameraTransform::~CameraTransform() {}

void CameraTransform::updateView()
{
	renderer->setView(view);
}

void CameraTransform::translate(float x, float y, float z)
{
	transformData.position += right * x + up * y - forward * z;

	view = lookAt(transformData.position, transformData.position + forward, vec3(0.0f, 1.0f, 0.0f));
	updateView();

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "viewPosition");
	glUniform3f(uniformLocation, transformData.position.x, transformData.position.y, transformData.position.z);
}

void CameraTransform::setPosition(float x, float y, float z)
{
	float translationX = x - transformData.position.x;
	float translationY = y - transformData.position.y;
	float translationZ = z - transformData.position.z;

	translate(translationX, translationY, translationZ);
}

void CameraTransform::rotate(float pitch, float yaw, float roll)
{
	transformData.rotation.x += pitch;
	if (transformData.rotation.x > 89.0f) transformData.rotation.x = 89.0f;
	if (transformData.rotation.x < -89.0f) transformData.rotation.x = -89.0f;

	transformData.rotation.y += yaw;
	transformData.rotation.z += roll;

	forward.x = cos(glm::radians(transformData.rotation.y)) * cos(glm::radians(transformData.rotation.x));
	forward.y = sin(glm::radians(transformData.rotation.x));
	forward.z = sin(glm::radians(transformData.rotation.y)) * cos(glm::radians(transformData.rotation.x));
	forward = glm::normalize(forward);

	right = normalize(cross(forward, vec3(0.0f, 1.0f, 0.0f)));
	up = normalize(cross(right, forward));

	view = lookAt(transformData.position, transformData.position + forward, vec3(0.0f, 1.0f, 0.0f));
	updateView();
}

void CameraTransform::setRotation(float pitch, float yaw, float roll)
{
	float rotationX = pitch - transformData.position.x;
	float rotationY = yaw - transformData.position.y;
	float rotationZ = roll - transformData.position.z;

	rotate(rotationX, rotationY, rotationZ);
}

void CameraTransform::setScale(float x, float y, float z) { cout << "Can not scale camera transform" << endl; }