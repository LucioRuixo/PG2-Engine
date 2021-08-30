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
	localModel.scale = mat4(1.0f);

	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	setScale(1.0f, 1.0f, 1.0f);
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

	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	setScale(1.0f, 1.0f, 1.0f);

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
	localModel.model = localModel.translation *
					   //localModel.rotation *
					   //localModel.rotationX * localModel.rotationY * localModel.rotationZ *
					   localModel.rotationZ * localModel.rotationY * localModel.rotationX *
					   localModel.scale;

	updateGlobalModel();
}

void Transform::updateGlobalModel()
{
	//TODO: Comprobar que el orden de multiplicaci�n est� bien
	if (parent) globalModel = parent->getGlobalModel() * localModel.model;
	//if (parent) globalModel = localModel.model * parent->getGlobalModel();
	else globalModel = localModel.model;
}

#pragma region Transformations
void Transform::translate(float x, float y, float z)
{
	//if (!children.empty())
	//	for (int i = 0; i < children.size(); i++) children[i]->translate(x, y, z);

	transformData.position.x += x;
	transformData.position.y += y;
	transformData.position.z += z;

	localModel.translation = glm::translate(mat4(1.0f), transformData.position);
	updateLocalModel();

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
	
	forward = glm::rotate(forward, radians(pitch), right);
	forward = glm::rotate(forward, radians(yaw), up);
	forward = normalize(forward);
	//cout << "forward - x: " << forward.x << " | y: " << forward.y << " | z: " << forward.z << endl;

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
	//TODO: comprobar que los c�lculos de forward, up y right est�n bien

	//cout << "right - x: " << right.x << " | y: " << right.y << " | z: " << right.z << endl;
	//cout << "up - x: " << up.x << " | y: " << up.y << " | z: " << up.z << endl;
	//cout << endl;

	if (pitch != 0.0f) localModel.model = glm::rotate(localModel.model, radians(pitch), vec3(1.0f, 0.0f, 0.0f));
	if (yaw != 0.0f) localModel.model = glm::rotate(localModel.model, radians(yaw), vec3(0.0f, 1.0f, 0.0f));
	if (roll != 0.0f) localModel.model = glm::rotate(localModel.model, radians(roll), vec3(0.0f, 0.0f, 1.0f));

	updateGlobalModel();
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

void Transform::rotateAroundPivot(float pitch, float yaw, float roll, Transform* pivot)
{
	rotate(pitch, yaw, roll);

	vec3 radius = transformData.position - pivot->getPosition();
	float newPositionX;
	float newPositionY;
	float newPositionZ;

	//Pitch
	if (pitch != 0.0f)
	{
		vec3 pitchRadius = vec3(0.0f, radius.y, radius.z);
		float angleToPitchStart = angle(vec3(0.0f, 0.0f, 1.0f), normalize(pitchRadius));

		if (transformData.position.y < pivot->getPosition().y)
		{
			newPositionY = sin((angleToPitchStart + radians(pitch))) * length(pitchRadius);
			newPositionZ = cos((angleToPitchStart + radians(pitch))) * length(pitchRadius);

			newPositionY *= -1.0f;
		}
		else
		{
			newPositionY = sin((angleToPitchStart - radians(pitch))) * length(pitchRadius);
			newPositionZ = cos((angleToPitchStart - radians(pitch))) * length(pitchRadius);
		}

		setPosition(transformData.position.x, pivot->getPosition().y + newPositionY, pivot->getPosition().z + newPositionZ);
	}

	//Yaw
	vec3 upInZAxis = normalize(vec3(pivot->getUp().x, pivot->getUp().y, 0.0f));
	float upZAxisTilt = angle(vec3(0.0f, 1.0f, 0.0f), upInZAxis);
	if (pivot->getUp().x < 0.0f) upZAxisTilt *= -1.0f;
	cout << "up Z axis tilt: " << upZAxisTilt << endl;

	if (yaw != 0.0f)
	{
		vec3 yawRadius = vec3(radius.x, 0.0f, radius.z);
		float angleToYawStart = angle(vec3(1.0f, 0.0f, 0.0f), normalize(yawRadius));

		if (transformData.position.z < pivot->getPosition().z)
		{
			newPositionZ = sin((angleToYawStart + radians(yaw))) * length(yawRadius);
			newPositionX = cos((angleToYawStart + radians(yaw))) * length(yawRadius);

			newPositionZ *= -1.0f;
		}
		else
		{
			newPositionZ = sin((angleToYawStart - radians(yaw))) * length(yawRadius);
			newPositionX = cos((angleToYawStart - radians(yaw))) * length(yawRadius);
		}

		setPosition(pivot->getPosition().x + newPositionX, transformData.position.y, pivot->getPosition().z + newPositionZ);
	}

	//Roll
	if (roll != 0.0f)
	{
		vec3 rollRadius = vec3(radius.x, radius.y, 0.0f);
		float angleToRollStart = angle(vec3(1.0f, 0.0f, 0.0f), normalize(rollRadius));

		if (transformData.position.y < pivot->getPosition().y)
		{
			newPositionY = sin((angleToRollStart - radians(roll) /*+ upZAxisTilt*/)) * length(rollRadius);
			newPositionX = cos((angleToRollStart - radians(roll) /*+ upZAxisTilt*/)) * length(rollRadius);

			newPositionY *= -1.0f;
		}
		else
		{
			newPositionY = sin((angleToRollStart + radians(roll)/* + upZAxisTilt*/)) * length(rollRadius);
			newPositionX = cos((angleToRollStart + radians(roll)/* + upZAxisTilt*/)) * length(rollRadius);
		}

		setPosition(pivot->getPosition().x + newPositionX, pivot->getPosition().y + newPositionY, transformData.position.z);
	}
}

void Transform::scale(float x, float y, float z)
{
	//if (!children.empty())
	//	for (int i = 0; i < children.size(); i++) children[i]->scale(x, y, z);

	transformData.scale.x += x;
	transformData.scale.y += y;
	transformData.scale.z += z;

	localModel.scale = glm::scale(mat4(1.0f), transformData.scale);
	updateLocalModel();

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