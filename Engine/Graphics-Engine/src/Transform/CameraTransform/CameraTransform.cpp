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

void CameraTransform::updateView(mat4 _view)
{
	view = _view;
	renderer->setView(view);
}

void CameraTransform::translate(float x, float y, float z)
{
	//localData.position += right * x + up * y - forward * z;
	//globalData = localData;
	Transform::translate(-x, y, z);

	vec3 adjustedForward = vec3(-forward.x, forward.y, forward.z);
	vec3 adjustedPosition = vec3(-localData.position.x, localData.position.y, localData.position.z);
	updateView(lookAt(adjustedPosition, adjustedPosition + adjustedForward, vec3(0.0f, 1.0f, 0.0f)));

	int uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "viewPosition");
	glUniform3f(uniformLocation, localData.position.x, localData.position.y, localData.position.z);

	//if (transformFrustum) frustum->getTransform()->translate(-x, y, z);
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
	//localData.rotation.x += pitch;
	//if (localData.rotation.x > 89.0f) localData.rotation.x = 89.0f;
	//if (localData.rotation.x < -89.0f) localData.rotation.x = -89.0f;
	//
	//localData.rotation.y += yaw;
	//if (roll != 0.0f) cout << "Can not roll camera" << endl;
	//
	//forward.x = sin(glm::radians(localData.rotation.y));
	//forward.y = sin(glm::radians(localData.rotation.x));
	//forward.z = cos(glm::radians(localData.rotation.x)) * cos(glm::radians(localData.rotation.y));
	//forward = glm::normalize(forward);
	//
	//right = normalize(cross(vec3(0.0f, 1.0f, 0.0f), forward));
	//
	//up = normalize(cross(forward, right));
	//
	//vec3 adjustedPosition = vec3(-localData.position.x, localData.position.y, localData.position.z);
	//updateView(lookAt(adjustedPosition, adjustedPosition + vec3(-forward.x, forward.y, forward.z), vec3(0.0f, 1.0f, 0.0f)));
	//
	//if (!children.empty())
	//	for (int i = 0; i < children.size(); i++) children[i]->updateGlobalModel();
	Transform::rotate(pitch, yaw, roll);

	vec3 adjustedForward = vec3(-forward.x, forward.y, forward.z);
	vec3 adjustedPosition = vec3(-localData.position.x, localData.position.y, localData.position.z);
	updateView(lookAt(adjustedPosition, adjustedPosition + adjustedForward, vec3(0.0f, 1.0f, 0.0f)));

	//if (transformFrustum) frustum->getTransform()->rotate(-pitch, -yaw, -roll);
	//if (transformFrustum) frustum->getTransform()->setRotation(vec3(-globalData.rotation.x, -globalData.rotation.y, 0.0f));
}

void CameraTransform::setRotation(float pitch, float yaw, float roll)
{
	float rotationX = pitch - localData.position.x;
	float rotationY = yaw - localData.position.y;
	float rotationZ = roll - localData.position.z;

	rotate(rotationX, rotationY, rotationZ);
}

void CameraTransform::setScale(float x, float y, float z) { cout << "Can not scale camera transform" << endl; }

#pragma region Frustum Culling
Frustum* CameraTransform::getFrustum()
{
	if (!frustumCulling)
	{
		cout << "Frustum culling is not enabled, returning null" << endl;
		return NULL;
	}
	else return frustum;
}

void CameraTransform::enableFrustumCulling(FrustumData frustumData)
{
	frustum = new Frustum(frustumData);
	frustumAttached = true;
	addChild(frustum->getTransform());

	frustumCulling = true;
}
void CameraTransform::disableFrustumCulling()
{
	if (frustum) delete frustum;
	frustumAttached = false;
	removeChild(frustum->getTransform());

	frustumCulling = false;
}
bool CameraTransform::getFrustumCulling() { return frustumCulling; }

void CameraTransform::toggleFrustumAttachment()
{
	frustumAttached = !frustumAttached;

	if (frustumAttached)
	{
		addChild(frustum->getTransform());
		frustum->getTransform()->setRotation(vec3(0.0f));
	}
	else
	{
		removeChild(frustum->getTransform());
		frustum->getTransform()->setRotation(vec3(0.0f, 180.0f, 0.0f));
	}

	frustum->getTransform()->setPosition(vec3(0.0f));
}
bool CameraTransform::getFrustumAttached() { return frustumAttached; }
#pragma endregion