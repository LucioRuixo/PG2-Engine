#include "Transform.h"

Transform::Transform()
{
	right = vec3(1.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	forward = vec3(0.0f, 0.0f, 1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	setScale(1.0f, 1.0f, 1.0f);

	localModel.model = mat4(1.0f);
	localModel.translation = mat4(1.0f);
	localModel.rotationX = mat4(1.0f);
	localModel.rotationY = mat4(1.0f);
	localModel.rotationZ = mat4(1.0f);
	localModel.rotation = mat4(1.0f);
	localModel.scale = mat4(1.0f);
}

Transform::Transform(vector<Transform*> _children)
{
	right = vec3(1.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	forward = vec3(0.0f, 0.0f, 1.0f);

	transformData.position = vec3(0.0f, 0.0f, 0.0f);
	transformData.rotation = vec3(0.0f, 0.0f, 0.0f);
	transformData.scale = vec3(1.0f, 1.0f, 1.0f);

	localModel.model = mat4(1.0f);
	localModel.translation = mat4(1.0f);
	localModel.rotationX = mat4(1.0f);
	localModel.rotationY = mat4(1.0f);
	localModel.rotationZ = mat4(1.0f);
	localModel.scale = mat4(1.0f);

	localModel.rotation = mat4(1.0f);

	for (int i = 0; i < _children.size(); i++) addChild(_children[i]);
}

Transform::~Transform()
{
	if (!children.empty())
	{
		for (int i = 0; i < children.size(); i++) if (children[i]) delete children[i];
		children.clear();
	}
}

float Transform::positiveDegrees(float degrees)
{
	if (degrees >= 0.0f) return degrees;

	return 360.0f + degrees;
}

float Transform::eulerAngles(float radians) { return radians * (180.0f / pi<float>()); }

vec3 Transform::eulerAngles(vec3 radians) { return vec3(eulerAngles(radians.x), eulerAngles(radians.y), eulerAngles(radians.z)); }

void Transform::decompose(mat4 matrix)
{
	vec3 translation, scale, skew;
	vec4 perspective;
	quat quatRotation;
	glm::decompose(matrix, scale, quatRotation, translation, skew, perspective);

	vec3 radiansRotation = glm::eulerAngles(quatRotation);
	vec3 eulerRotation = eulerAngles(radiansRotation);
	//cout << "decomposed rotation: " << eulerRotation.x << " | " << eulerRotation.y << " | " << eulerRotation.z << endl;
}

void Transform::decompose(mat4 matrix, vec3& translation, vec3& eulerRotation, vec3& scale)
{
	vec3 skew;
	vec4 perspective;
	quat quatRotation;
	glm::decompose(matrix, scale, quatRotation, translation, skew, perspective);

	vec3 radiansRotation = glm::eulerAngles(quatRotation);
	eulerRotation = eulerAngles(radiansRotation);
	cout << "decomposed rotation: " << eulerRotation.x << " | " << eulerRotation.y << " | " << eulerRotation.z << endl;
}

void Transform::decompose(mat4 matrix, vec3& translation, quat& quatRotation, vec3& scale)
{
	vec3 skew;
	vec4 perspective;
	glm::decompose(matrix, scale, quatRotation, translation, skew, perspective);

	vec3 radiansRotation = glm::eulerAngles(quatRotation);
	vec3 eulerRotation = eulerAngles(radiansRotation);
	//cout << "decomposed rotation: " << eulerRotation.x << " | " << eulerRotation.y << " | " << eulerRotation.z << endl;
}

void Transform::processRotation(float pitch, float yaw, float roll)
{
	transformData.rotation.x += pitch;
	transformData.rotation.y += yaw;
	transformData.rotation.z += roll;

	if (transformData.rotation.x >= 360.0f) transformData.rotation.x -= 360.0f;
	else if (transformData.rotation.x < 0.0f) transformData.rotation.x += 360.0f;

	if (transformData.rotation.y >= 360.0f) transformData.rotation.y -= 360.0f;
	else if (transformData.rotation.y < 0.0f) transformData.rotation.y += 360.0f;

	if (transformData.rotation.z >= 360.0f) transformData.rotation.z -= 360.0f;
	else if (transformData.rotation.z < 0.0f) transformData.rotation.z += 360.0f;

	localModel.rotation = glm::rotate(localModel.rotation, radians(pitch), vec3(1.0f, 0.0f, 0.0f));
	localModel.rotation = glm::rotate(localModel.rotation, radians(yaw)  , vec3(0.0f, 1.0f, 0.0f));
	localModel.rotation = glm::rotate(localModel.rotation, radians(roll) , vec3(0.0f, 0.0f, 1.0f));

	updateLocalModel();
	updateDirectionVectors(pitch, yaw, roll);
}

void Transform::updateDirectionVectors(float pitch, float yaw, float roll)
{
	vec3 newRight = right;
	vec3 newUp = up;
	vec3 newForward = forward;

	if (pitch != 0.0f)
	{
		newRight = normalize(glm::rotate(newRight, radians(pitch), right));
		newUp = normalize(glm::rotate(newUp, radians(pitch), right));
		newForward = normalize(glm::rotate(newForward, radians(pitch), right));
	}

	if (yaw != 0.0f)
	{
		newRight = normalize(glm::rotate(newRight, radians(-yaw), up));
		newUp = normalize(glm::rotate(newUp, radians(-yaw), up));
		newForward = normalize(glm::rotate(newForward, radians(-yaw), up));
	}

	if (roll != 0.0f)
	{
		newRight = normalize(glm::rotate(newRight, radians(-roll), forward));
		newUp = normalize(glm::rotate(newUp, radians(-roll), forward));
		newForward = normalize(glm::rotate(newForward, radians(-roll), forward));
	}

	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->updateChildrenDirectionVectors(pitch, yaw, roll, right, up, forward);

	right = newRight;
	up = newUp;
	forward = newForward;
}

void Transform::updateChildrenDirectionVectors(float pitch, float yaw, float roll, vec3 xAxis, vec3 yAxis, vec3 zAxis)
{
	vec3 newRight = right;
	vec3 newUp = up;
	vec3 newForward = forward;
	
	if (pitch != 0.0f)
	{
		newRight = normalize(glm::rotate(newRight, radians(pitch), xAxis));
		newUp = normalize(glm::rotate(newUp, radians(pitch), xAxis));
		newForward = normalize(glm::rotate(newForward, radians(pitch), xAxis));
	}
	
	if (yaw != 0.0f)
	{
		newRight = normalize(glm::rotate(newRight, radians(-yaw), yAxis));
		newUp = normalize(glm::rotate(newUp, radians(-yaw), yAxis));
		newForward = normalize(glm::rotate(newForward, radians(-yaw), yAxis));
	}
	
	if (roll != 0.0f)
	{
		newRight = normalize(glm::rotate(newRight, radians(-roll), zAxis));
		newUp = normalize(glm::rotate(newUp, radians(-roll), zAxis));
		newForward = normalize(glm::rotate(newForward, radians(-roll), zAxis));
	}
	
	right = newRight;
	up = newUp;
	forward = newForward;
	
	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->updateChildrenDirectionVectors(pitch, yaw, roll, xAxis, yAxis, zAxis);
}

void Transform::updateLocalModel()
{
	localModel.model = localModel.translation * localModel.rotation * localModel.scale;

	updateGlobalModel();
}

void Transform::updateGlobalModel()
{
	if (parent) globalModel = parent->getGlobalModel() * localModel.model;
	else globalModel = localModel.model;

	if (!children.empty()) for (int i = 0; i < children.size(); i++) children[i]->updateGlobalModel();
}

void Transform::updateGlobalModel(mat4 other) { globalModel = other * localModel.model; }

#pragma region Transformations
void Transform::translate(float x, float y, float z)
{
	transformData.position.x += x;
	transformData.position.y += y;
	transformData.position.z += z;
	
	vec3 position = transformData.position;
	position.x *= -1.0f;
	localModel.translation = glm::translate(mat4(1.0f), position);

	updateLocalModel();
}

void Transform::setPosition(float x, float y, float z)
{
	float translationX = x - transformData.position.x;
	float translationY = y - transformData.position.y;
	float translationZ = z - transformData.position.z;

	translate(translationX, translationY, translationZ);
}
vec3 Transform::getPosition() { return vec3(-transformData.position.x, transformData.position.y, transformData.position.z); }

vec3 Transform::getGlobalPosition()
{
	vec3 position = vec3(globalModel * vec4(transformData.position, 1.0f));
	return vec3(-position.x, position.y, position.z);
}

void Transform::rotate(float pitch, float yaw, float roll)
{
	if (pitch != 0.0f) processRotation(pitch, 0.0f, 0.0f);
	if (yaw   != 0.0f) processRotation(0.0f, yaw, 0.0f);
	if (roll  != 0.0f) processRotation(0.0f, 0.0f, roll);
}

void Transform::setRotation(float pitch, float yaw, float roll)
{
	float rotationX = positiveDegrees(pitch - transformData.rotation.x);
	float rotationY = positiveDegrees(yaw - transformData.rotation.y);
	float rotationZ = positiveDegrees(roll - transformData.rotation.z);

	if (rotationX != 0.0f) processRotation(rotationX, 0.0f, 0.0f);
	if (rotationY != 0.0f) processRotation(0.0f, rotationY, 0.0f);
	if (rotationZ != 0.0f) processRotation(0.0f, 0.0f, rotationZ);

}
vec3 Transform::getRotation() { return transformData.rotation; }

vec3 Transform::getGlobalRotation()
{
	vec3 rotation = getRotation();
	if (parent) rotation += parent->getGlobalRotation();

	return rotation;
}

void Transform::scale(float x, float y, float z)
{
	transformData.scale.x += x;
	transformData.scale.y += y;
	transformData.scale.z += z;

	localModel.scale = glm::scale(mat4(1.0f), transformData.scale);
	updateLocalModel();
}

void Transform::setScale(float x, float y, float z)
{
	float scaleX = x - transformData.scale.x;
	float scaleY = y - transformData.scale.y;
	float scaleZ = z - transformData.scale.z;

	scale(scaleX, scaleY, scaleZ);
}
vec3 Transform::getScale() { return transformData.scale; }

vec3 Transform::getRight() { return right; }

vec3 Transform::getUp() { return up; }

vec3 Transform::getForward() { return forward; }

mat4 Transform::getLocalModel() { return localModel.model; }

mat4 Transform::getGlobalModel() { return globalModel; }
#pragma endregion

#pragma region Children
vector<Transform*> Transform::getChildren() { return children; }

void Transform::addChild(Transform* child)
{
	children.push_back(child);
	child->setParent(this);
}

void Transform::removeChild(Transform* child)
{
	int i = 0;
	vector<Transform*>::iterator iterator;
	for (iterator = children.begin(); iterator < children.end(); iterator++)
	{
		if (*iterator == child)
		{
			children.erase(iterator);
			child->setParent(NULL);

			return;
		}

		i++;
	}

	cout << "Child transform intended to be removed was not found" << endl;
}
#pragma endregion

#pragma region Parent
void Transform::setParent(Transform* _parent)
{
	if (parent == _parent) return;

	if (parent) parent->removeChild(this);

	parent = _parent;
}

Transform* Transform::getParent() { return parent; }
#pragma endregion