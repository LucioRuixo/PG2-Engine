#include "Transform.h"

Transform::Transform()
{
	forward = vec3(0.0f, 0.0f, 1.0f);
	upVector = vec3(0.0f, 1.0f, 0.0f);

	transformData.position = vec3(0.0f, 0.0f, 0.0f);
	transformData.rotation = vec3(0.0f, 0.0f, 0.0f);
	transformData.scale = vec3(1.0f, 1.0f, 1.0f);

	model = mat4(1.0f);

	trsMatrix.translation = mat4(1.0f);
	trsMatrix.rotationX = mat4(1.0f);
	trsMatrix.rotationY = mat4(1.0f);
	trsMatrix.rotationZ = mat4(1.0f);
	trsMatrix.scale = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	setScale(1.0f, 1.0f, 1.0f);
}

Transform::Transform(vector<Transform*> _children)
{
	forward = vec3(0.0f, 0.0f, 1.0f);
	upVector = vec3(0.0f, 1.0f, 0.0f);

	transformData.position = vec3(0.0f, 0.0f, 0.0f);
	transformData.rotation = vec3(0.0f, 0.0f, 0.0f);
	transformData.scale = vec3(1.0f, 1.0f, 1.0f);

	model = mat4(1.0f);

	trsMatrix.translation = mat4(1.0f);
	trsMatrix.rotationX = mat4(1.0f);
	trsMatrix.rotationY = mat4(1.0f);
	trsMatrix.rotationZ = mat4(1.0f);
	trsMatrix.scale = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	setScale(1.0f, 1.0f, 1.0f);

	addChildren(_children);
}

Transform::~Transform()
{
	if (!children.empty())
	{
		for (int i = 0; i < children.size(); i++) if (children[i]) delete children[i];
		children.clear();
	}
}

void Transform::updateModel()
{
	model = trsMatrix.translation *
			trsMatrix.rotationX * trsMatrix.rotationY * trsMatrix.rotationZ *
			trsMatrix.scale;
}

#pragma region Transformations
void Transform::translate(float x, float y, float z)
{
	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->translate(x, y, z);

	transformData.position.x += x;
	transformData.position.y += y;
	transformData.position.z += z;

	trsMatrix.translation = glm::translate(mat4(1.0f), transformData.position);
	updateModel();
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

	vec3 xAxis = vec3(1.0f, 0.0f, 0.0f);
	vec3 yAxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 zAxis = vec3(0.0f, 0.0f, 1.0f);
	trsMatrix.rotationX = glm::rotate(mat4(1.0f), radians(transformData.rotation.x), xAxis);
	trsMatrix.rotationY = glm::rotate(mat4(1.0f), radians(transformData.rotation.y), yAxis);
	trsMatrix.rotationZ = glm::rotate(mat4(1.0f), radians(transformData.rotation.z), zAxis);
	updateModel();

	if (!children.empty())
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->getTRS().rotationX *= trsMatrix.rotationX;
			children[i]->getTRS().rotationY *= trsMatrix.rotationY;
			children[i]->getTRS().rotationZ *= trsMatrix.rotationZ;

			children[i]->updateModel();
		}

		//for (int i = 0; i < children.size(); i++) children[i]->rotate(pitch, yaw, roll);
	}
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
	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->scale(x, y, z);

	transformData.scale.x += x;
	transformData.scale.y += y;
	transformData.scale.z += z;

	trsMatrix.scale = glm::scale(mat4(1.0f), transformData.scale);
	updateModel();
}

void Transform::setScale(float x, float y, float z)
{
	float scaleX = x - transformData.scale.x;
	float scaleY = y - transformData.scale.y;
	float scaleZ = z - transformData.scale.z;

	scale(scaleX, scaleY, scaleZ);
}
vec3 Transform::getScale() { return transformData.scale; }

mat4 Transform::getModel() { return model; }

TRSMatrix Transform::getTRS() { return trsMatrix; }
#pragma endregion

#pragma region Children
vector<Transform*> Transform::getChildren() { return children; }

void Transform::addChild(Transform* child) { children.push_back(child); }

void Transform::addChildren(vector<Transform*> newChildren) { children.insert(children.end(), newChildren.begin(), newChildren.end()); }
#pragma endregion