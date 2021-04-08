#include "Camera.h"

Camera::Camera(Renderer* _renderer)
{
	renderer = _renderer;

	transform = new Transform();
}

Camera::~Camera() { if (transform) delete transform; }

void Camera::updateViewMatrix()
{
	matrixData.mainMatrix = matrixData.translation *
							matrixData.rotationX * matrixData.rotationY * matrixData.rotationZ *
							matrixData.scale;

	renderer->setView(renderer->getShaderProgram(), matrixData.mainMatrix);
}

void Camera::setPosition(float x, float y, float z)
{
	matrixData.translation = glm::translate(mat4(1.0f), vec3(-x, -y, -z));
	updateViewMatrix();

	transform->position = vec3(x, y, z);

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "viewPosition");
	glUniform3f(uniformLocation, transform->position.x, transform->position.y, transform->position.z);
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
	transform->position = vec3(newTransformX, newTransformY, newTransformZ);

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(), "viewPosition");
	glUniform3f(uniformLocation, transform->position.x, transform->position.y, transform->position.z);
}

void Camera::setRotation(float x, float y, float z)
{
	vec3 xAxis = vec3(1.0f, 0.0f, 0.0f);
	vec3 yAxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 zAxis = vec3(0.0f, 0.0f, 1.0f);

	matrixData.rotationX = rotate(mat4(1.0f), -x, xAxis);
	matrixData.rotationY = rotate(mat4(1.0f), -y, yAxis);
	matrixData.rotationZ = rotate(mat4(1.0f), -z, zAxis);
	updateViewMatrix();

	transform->rotation = vec3(x, y, z);
}