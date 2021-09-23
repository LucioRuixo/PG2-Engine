#include "Camera.h"

Camera::Camera(Renderer* _renderer) : Entity()
{
	renderer = _renderer;

	transform = new CameraTransform(renderer);

	//Cube* childCube = new Cube(vec3(0.1f, 1.0f, 0.1f));
	//addChild(childCube);
	//childCube->getTransform()->setPosition(transform->getForward().x * 5.0f, transform->getForward().y * 5.0f, transform->getForward().z * 5.0f);
}

Camera::~Camera() { if (transform) delete transform; }

CameraTransform* Camera::getTransform() { return transform; }

#pragma region Children
vector<Entity*> Camera::getChildren() { return children; }

void Camera::addChild(Entity* child)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] == child)
		{
			cout << "Entity intended to be added to parent is already a child" << endl;

			return;
		}
	}

	children.push_back(child);
	child->setParent(this);

	transform->addChild(child->getTransform());
}

void Camera::removeChild(Entity* child)
{
	vector<Entity*>::iterator iterator;
	for (iterator = children.begin(); iterator < children.end(); iterator++)
	{
		if (*iterator == child)
		{
			children.erase(iterator);
			transform->removeChild(child->getTransform());
			child->setParent(NULL);

			return;
		}
	}

	cout << "Child entity intended to be removed from parent was not found" << endl;
}
#pragma endregion

#pragma region Parent
void Camera::setParent(Entity* _parent)
{
	if (parent == _parent) return;

	if (parent) parent->removeChild(this);

	parent = _parent;
	if (parent) transform->setParent(parent->getTransform());
	else transform->setParent(NULL);
}

Entity* Camera::getParent() { return parent; }
#pragma endregion