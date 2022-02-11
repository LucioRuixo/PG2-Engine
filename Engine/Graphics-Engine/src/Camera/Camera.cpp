#include "Camera.h"

Camera::Camera(Renderer* _renderer) : Entity(false)
{
	renderer = _renderer;

	transform = new CameraTransform(renderer);
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

#pragma region Frustum Culling
Frustum* Camera::getFrustum()
{ 
	if (!frustumCulling)
	{
		cout << "Frustum culling is not enabled, returning null" << endl;
		return NULL;
	}
	else return frustum;
}

void Camera::enableFrustumCulling(FrustumData frustumData)
{
	frustum = new Frustum(frustumData, transform);
	//addChild(dynamic_cast<Entity*>(frustum));

	frustumCulling = true;
}

void Camera::disableFrustumCulling()
{
	if (frustum) delete frustum;
	//removeChild(dynamic_cast<Entity*>(frustum));

	frustumCulling = false;
}

void Camera::processFrustumCulling(Entity* entity) { if (frustum->isInside(entity)) entity->draw(); }
#pragma endregion

#pragma region Collision Box
vector<vec3> Camera::getCollisionVertices()
{
	cout << "Can not generate collision vertices for this class (Camera)" << endl;
	return vector<vec3>();
}
#pragma endregion

#pragma region Rendering
void Camera::draw()
{
	if (frustumCulling) drawFrustum();

	Entity::draw();
}

void Camera::drawFrustum()
{
	if (frustumCulling)
	{
		if (frustum) frustum->draw();
		else cout << "Can not draw camera frustum: frustum object is null" << endl;
	}
	else cout << "Can not draw camera frustum: frustum culling is not enabled" << endl;
}

void Camera::drawEntities()
{
	int drawnEntities = 0;

	for (int i = 0; i < Entity::getRenderizableEntities().size(); i++)
	{
		Entity* entity = Entity::getRenderizableEntities()[i];

		if (entity->getShouldBeDrawn())
		{
			//if (frustumCulling) processFrustumCulling(entity);
			if (frustumCulling)
			{
				if (frustum->isInside(entity))
				{
					entity->draw();
					drawnEntities++;
				}
			}
			else
			{
				entity->draw();
				drawnEntities++;
			}
		}
	}

	cout << "drawn entities: " << drawnEntities << endl;
}
#pragma endregion