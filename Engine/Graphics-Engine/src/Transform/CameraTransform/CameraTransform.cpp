#include "CameraTransform.h"

CameraTransform::CameraTransform(Renderer* _renderer) : Transform()
{
	//forward = vec3(0.0f, 0.0f, -1.0f);
	view = mat4(1.0f);

	renderer = _renderer;

	//cout << endl;
	//cout << "right: " << right.x << " | y: " << right.y << " | z: " << right.z << endl;
	//cout << "up: " << up.x << " | y: " << up.y << " | z: " << up.z << endl;
	//cout << "forward: " << forward.x << " | y: " << forward.y << " | z: " << forward.z << endl;
}

CameraTransform::~CameraTransform() {}

void CameraTransform::updateView() { renderer->setView(view); }

void CameraTransform::translate(float x, float y, float z)
{
	//Transform::translate(x, y, z);

	localData.position += right * x + up * y - forward * z;
	//cout << endl;
	//cout << "camera position: " << transformData.position.x << ", " << transformData.position.y << ", " << transformData.position.z << endl;

	vec3 adjustedPosition = vec3(-localData.position.x, localData.position.y, localData.position.z);
	view = lookAt(adjustedPosition, adjustedPosition + vec3(-forward.x, forward.y, forward.z), vec3(0.0f, 1.0f, 0.0f));
	updateView();

	//if (!children.empty())
	//	for (int i = 0; i < children.size(); i++) children[i]->updateGlobalModel();

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "viewPosition");
	glUniform3f(uniformLocation, localData.position.x, localData.position.y, localData.position.z);
}

void CameraTransform::setPosition(float x, float y, float z)
{
	float translationX = x - localData.position.x;
	float translationY = y - localData.position.y;
	float translationZ = z - localData.position.z;

	translate(translationX, translationY, translationZ);
}
vec3 CameraTransform::getPosition() { return localData.position; }

void CameraTransform::rotate(float pitch, float yaw, float roll)
{
	localData.rotation.x += pitch;
	if (localData.rotation.x > 89.0f) localData.rotation.x = 89.0f;
	if (localData.rotation.x < -89.0f) localData.rotation.x = -89.0f;

	localData.rotation.y += yaw;
	if (roll != 0.0f) cout << "Can not roll camera" << endl;

	//cout << "rotation - x: " << transformData.rotation.x << " | y: " << transformData.rotation.y << " | z: " << transformData.rotation.z << endl;

	forward.x = sin(glm::radians(localData.rotation.y));
	forward.y = sin(glm::radians(localData.rotation.x));
	forward.z = cos(glm::radians(localData.rotation.x)) * cos(glm::radians(localData.rotation.y));
	forward = glm::normalize(forward);
	//cout << "forward - x: " << forward.x << " | y: " << forward.y << " | z: " << forward.z << endl;

	right = normalize(cross(vec3(0.0f, 1.0f, 0.0f), forward));
	//cout << "right - x: " << right.x << " | y: " << right.y << " | z: " << right.z << endl;

	up = normalize(cross(forward, right));
	//cout << "up - x: " << up.x << " | y: " << up.y << " | z: " << up.z << endl;

	vec3 adjustedPosition = vec3(-localData.position.x, localData.position.y, localData.position.z);
	view = lookAt(adjustedPosition, adjustedPosition + vec3(-forward.x, forward.y, forward.z), vec3(0.0f, 1.0f, 0.0f));
	updateView();

	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->updateGlobalModel();
}

void CameraTransform::setRotation(float pitch, float yaw, float roll)
{
	float rotationX = pitch - localData.position.x;
	float rotationY = yaw - localData.position.y;
	float rotationZ = roll - localData.position.z;

	rotate(rotationX, rotationY, rotationZ);
}

void CameraTransform::setScale(float x, float y, float z) { cout << "Can not scale camera transform" << endl; }