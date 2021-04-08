#include"Entity2D.h"

Entity2D::Entity2D(Renderer* _renderer) : Entity(_renderer)
{
	renderer = _renderer;
	bounds.min = bounds.max = vec2(0.0f, 0.0f);
}

Entity2D::Entity2D(Renderer* _renderer, vec2 _boundsMin, vec2 _boundsMax) : Entity(_renderer)
{
	renderer = _renderer;

	bounds.min = _boundsMin;
	bounds.max = _boundsMax;
	bounds.size = vec2(bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y);
}

void Entity2D::setPosition(float x, float y, float z)
{
	transform->position = vec3(x, y, z);

	matrixData.translation = glm::translate(glm::mat4(1.0f), transform->position);
	updateModelMatrix();

	bounds.min.x = transform->position.x - bounds.size.x / 2.0f;
	bounds.max.x = transform->position.x + bounds.size.x / 2.0f;
	bounds.min.y = transform->position.y - bounds.size.y / 2.0f;
	bounds.max.y = transform->position.y + bounds.size.y / 2.0f;
}

void Entity2D::setScale(float x, float y, float z)
{
	transform->scale = vec3(x, y, z);

	matrixData.scale = glm::scale(glm::mat4(1.0f), transform->scale);
	updateModelMatrix();

	bounds.size.x = x;
	bounds.size.y = y;
	bounds.min.x = transform->position.x - bounds.size.x / 2.0f;
	bounds.max.x = transform->position.x + bounds.size.x / 2.0f;
	bounds.min.y = transform->position.y - bounds.size.y / 2.0f;
	bounds.max.y = transform->position.y + bounds.size.y / 2.0f;
}

void Entity2D::setBounds(Bounds _bounds)
{
	bounds = _bounds;
}

void Entity2D::translateBounds(float translationX, float translationY)
{
	bounds.min.x += translationX;
	bounds.max.x += translationX;

	bounds.min.y += translationY;
	bounds.max.y += translationY;
}

Bounds Entity2D::getBounds()
{
	return bounds;
}