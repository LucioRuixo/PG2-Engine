#include "Transform.h"

Transform::Transform()
{
	right = vec3(1.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	forward = vec3(0.0f, 0.0f, 1.0f);

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
	right = vec3(1.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	forward = vec3(0.0f, 0.0f, 1.0f);

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

	//right = rotateY(right, radians(-yaw));
	//right = rotateZ(right, radians(-roll));
	//right = normalize(right);
	
	//up = rotateX(up, radians(pitch));
	//up = rotateZ(up, radians(-roll));
	//up = normalize(up);
	
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

	//cout << "right - x: " << right.x << " | y: " << right.y << " | z: " << right.z << endl;
	//cout << "up - x: " << up.x << " | y: " << up.y << " | z: " << up.z << endl;

	//cout << "XY: " << angle(right, up) << endl;
	//cout << "XZ: " << angle(right, forward) << endl;
	//cout << "YZ: " << angle(up, forward) << endl;
	cout << endl;

	//trsMatrix.rotationX = glm::rotate(mat4(1.0f), radians(transformData.rotation.x), vec3(1.0f, 0.0f, 0.0f));
	//trsMatrix.rotationY = glm::rotate(mat4(1.0f), radians(transformData.rotation.y), vec3(0.0f, 1.0f, 0.0f));
	//trsMatrix.rotationZ = glm::rotate(mat4(1.0f), radians(transformData.rotation.z), vec3(0.0f, 0.0f, 1.0f));
	trsMatrix.rotationX = glm::rotate(mat4(1.0f), radians(transformData.rotation.x), right);
	trsMatrix.rotationY = glm::rotate(mat4(1.0f), radians(transformData.rotation.y), up);
	trsMatrix.rotationZ = glm::rotate(mat4(1.0f), radians(transformData.rotation.z), forward);
	updateModel();

	if (!children.empty())
		for (int i = 0; i < children.size(); i++) children[i]->rotateAroundPivot(pitch, yaw, roll, this);
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

vec3 Transform::getRight() { return right; }

vec3 Transform::getUp() { return up; }

vec3 Transform::getForward() { return forward; }

mat4 Transform::getModel() { return model; }

TRSMatrix Transform::getTRS() { return trsMatrix; }
#pragma endregion

#pragma region Children
vector<Transform*> Transform::getChildren() { return children; }

void Transform::addChild(Transform* child) { children.push_back(child); }

void Transform::addChildren(vector<Transform*> newChildren) { children.insert(children.end(), newChildren.begin(), newChildren.end()); }

void Transform::removeChild(Transform* child)
{
	int i = 0;
	vector<Transform*>::iterator iterator;
	for (iterator = children.begin(); iterator < children.end(); iterator++)
	{
		if (*iterator == child)
		{
			children.erase(iterator);

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

	if (parent != NULL) parent->removeChild(this);

	parent = _parent;
}

Transform* Transform::getParent() { return parent; }
#pragma endregion