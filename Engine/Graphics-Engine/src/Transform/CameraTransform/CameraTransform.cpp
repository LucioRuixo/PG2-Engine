#include "CameraTransform.h"

CameraTransform::CameraTransform(Renderer* _renderer) : Transform()
{
	//forward = vec3(0.0f, 0.0f, -1.0f);
	view = mat4(1.0f);

	renderer = _renderer;

	cout << endl;
	cout << "right: " << right.x << " | y: " << right.y << " | z: " << right.z << endl;
	cout << "up: " << up.x << " | y: " << up.y << " | z: " << up.z << endl;
	cout << "forward: " << forward.x << " | y: " << forward.y << " | z: " << forward.z << endl;
}

CameraTransform::~CameraTransform() {}

void CameraTransform::updateView()
{
	renderer->setView(view);
}

void CameraTransform::translate(float x, float y, float z)
{
	transformData.position += -right * x + up * y - forward * z;

	view = lookAt(transformData.position, transformData.position + vec3(-forward.x, forward.y, forward.z), vec3(0.0f, 1.0f, 0.0f));
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
	if (roll != 0.0f) cout << "Can not roll camera" << endl;

	//cout << "rotation - x: " << transformData.rotation.x << " | y: " << transformData.rotation.y << " | z: " << transformData.rotation.z << endl;

	forward.x = sin(glm::radians(transformData.rotation.y));
	forward.y = sin(glm::radians(transformData.rotation.x));
	forward.z = cos(glm::radians(transformData.rotation.x)) * cos(glm::radians(transformData.rotation.y));
	forward = glm::normalize(forward);
	//cout << "forward - x: " << forward.x << " | y: " << forward.y << " | z: " << forward.z << endl;

	right = normalize(cross(vec3(0.0f, 1.0f, 0.0f), forward));
	//cout << "right - x: " << right.x << " | y: " << right.y << " | z: " << right.z << endl;

	up = normalize(cross(forward, right));
	//cout << "up - x: " << up.x << " | y: " << up.y << " | z: " << up.z << endl;

	view = lookAt(transformData.position, transformData.position + vec3(-forward.x, forward.y, forward.z), vec3(0.0f, 1.0f, 0.0f));
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