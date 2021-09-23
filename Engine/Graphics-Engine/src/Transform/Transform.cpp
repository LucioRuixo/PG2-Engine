#include "Transform.h"

Transform::Transform()
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

void Transform::updateLocalModel()
{
	//TODO: revisar esto y rotate() para que la rotación en todos los ejes sea local
	localModel.model = localModel.translation * localModel.rotation * localModel.scale;

	//localModel.model = localModel.translation * localModel.rotation * localModel.scale;

	//localModel.model = mat4(1.0f);
	
	//localModel.model = glm::translate(localModel.model, vec3(transformData.position.x, transformData.position.y, transformData.position.z));
	
	//localModel.model = glm::rotate(localModel.model, radians(transformData.rotation.x), vec3(1.0f, 0.0f, 0.0f));
	//localModel.model = glm::rotate(localModel.model, radians(transformData.rotation.y), vec3(0.0f, 1.0f, 0.0f));
	//localModel.model = glm::rotate(localModel.model, radians(transformData.rotation.z), vec3(0.0f, 0.0f, 1.0f));
	
	//localModel.model = glm::scale(localModel.model, vec3(transformData.scale.x, transformData.scale.y, transformData.scale.z));

	updateGlobalModel();
}

void Transform::updateGlobalModel()
{
	//TODO: Comprobar que el orden de multiplicación esté bien
	if (parent) globalModel = parent->getGlobalModel() * localModel.model;
	//if (parent) globalModel = localModel.model * parent->getGlobalModel();
	else globalModel = localModel.model;
}

void Transform::updateGlobalModel(mat4 other)
{
	if (parent) globalModel = other * localModel.model;
}

#pragma region Transformations
void Transform::translate(float x, float y, float z)
{
	transformData.position.x += x;
	transformData.position.y += y;
	transformData.position.z += z;

	cout << "translating to <" << transformData.position.x << ", " << transformData.position.y << ", " << transformData.position.z << ">" << endl;
	
	localModel.translation = glm::translate(mat4(1.0f), transformData.position);
	updateLocalModel();

	//localModel.model = glm::translate(localModel.model, vec3(x, y, z));
	//updateGlobalModel();

	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->updateGlobalModel();
}

void Transform::setPosition(float x, float y, float z)
{
	float translationX = x - transformData.position.x;
	float translationY = y - transformData.position.y;
	float translationZ = z - transformData.position.z;

	translate(translationX, translationY, translationZ);
}
vec3 Transform::getPosition() { return transformData.position; }

void Transform::rotate(float pitch, float yaw, float roll)
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
	
	forward = glm::rotate(forward, radians(pitch), right);
	forward = glm::rotate(forward, radians(yaw), up);
	forward = normalize(forward);

	if (forward.z > 0.0f)
	{
		right = normalize(cross(vec3(0.0f, 1.0f, 0.0f), forward));
		up = normalize(cross(forward, right));
	}
	else
	{
		right = normalize(cross(forward, vec3(0.0f, 1.0f, 0.0f)));
		up = normalize(cross(right, forward));
	}
	//TODO: comprobar que los cálculos de forward, up y right estén bien
	
	//cout << endl;
	//cout << "right - x: " << right.x << " | y: " << right.y << " | z: " << right.z << endl;
	//cout << "up - x: " << up.x << " | y: " << up.y << " | z: " << up.z << endl;
	//cout << "forward - x: " << forward.x << " | y: " << forward.y << " | z: " << forward.z << endl;

	localModel.rotationZ = glm::rotate(mat4(1.0f), radians(transformData.rotation.z), vec3(0.0f, 0.0f, 1.0f));
	localModel.rotationY = glm::rotate(mat4(1.0f), radians(transformData.rotation.y), vec3(0.0f, 1.0f, 0.0f));
	localModel.rotationX = glm::rotate(mat4(1.0f), radians(transformData.rotation.x), vec3(1.0f, 0.0f, 0.0f));
	localModel.rotation = localModel.rotationZ * localModel.rotationY * localModel.rotationX;
	updateLocalModel();

	//if (pitch != 0.0f) localModel.model = glm::rotate(localModel.model, radians(pitch), vec3(1.0f, 0.0f, 0.0f));
	//if (yaw != 0.0f) localModel.model = glm::rotate(localModel.model, radians(yaw), vec3(0.0f, 1.0f, 0.0f));
	//if (roll != 0.0f) localModel.model = glm::rotate(localModel.model, radians(roll), vec3(0.0f, 0.0f, 1.0f));
	//updateGlobalModel();

	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->updateGlobalModel();
}

void Transform::setRotation(float pitch, float yaw, float roll)
{
	float rotationX = pitch - transformData.rotation.x;
	float rotationY = yaw - transformData.rotation.y;
	float rotationZ = roll - transformData.rotation.z;

	rotate(rotationX, rotationY, rotationZ);
}
vec3 Transform::getRotation() { return transformData.rotation; }

void Transform::scale(float x, float y, float z)
{
	transformData.scale.x += x;
	transformData.scale.y += y;
	transformData.scale.z += z;

	localModel.scale = glm::scale(mat4(1.0f), transformData.scale);
	updateLocalModel();

	//localModel.model = glm::scale(localModel.model, vec3(x, y, z));
	//updateGlobalModel();

	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->updateGlobalModel();
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

//ModelMatrix Transform::getTRS() { return model; }
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