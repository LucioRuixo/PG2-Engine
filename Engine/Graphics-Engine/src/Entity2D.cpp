#include"Entity2D.h"

Entity2D::Entity2D(Renderer* _render) : Entity(_render) {
	renderer = _render;
	bounds.min = bounds.max = vec2(0.0f, 0.0f);
}

Entity2D::Entity2D(Renderer* _render, vec2 _boundsMin, vec2 _boundsMax) : Entity(_render) {
	renderer = _render;

	bounds.min = _boundsMin;
	bounds.max = _boundsMax;
	bounds.size = vec2(bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y);
}

void Entity2D::SetPosition(float x, float y, float z) {
	transform.position[0] = x;
	transform.position[1] = y;
	transform.position[2] = z;

	internalData.translate = glm::translate(glm::mat4(1.0f), transform.position);
	UpdateMatrixModel();

	bounds.min.x = transform.position.x - bounds.size.x / 2.0f;
	bounds.max.x = transform.position.x + bounds.size.x / 2.0f;
	bounds.min.y = transform.position.y - bounds.size.y / 2.0f;
	bounds.max.y = transform.position.y + bounds.size.y / 2.0f;
}

void Entity2D::SetScale(float x, float y, float z) {
	transform.scale[0] = x;
	transform.scale[1] = y;
	transform.scale[2] = z;

	internalData.scale = glm::scale(glm::mat4(1.0f), transform.scale);
	UpdateMatrixModel();

	bounds.size.x = x;
	bounds.size.y = y;
	bounds.min.x = transform.position.x - bounds.size.x / 2.0f;
	bounds.max.x = transform.position.x + bounds.size.x / 2.0f;
	bounds.min.y = transform.position.y - bounds.size.y / 2.0f;
	bounds.max.y = transform.position.y + bounds.size.y / 2.0f;
}

void Entity2D::setBounds(Bounds _bounds)
{
	bounds = _bounds;
}

void Entity2D::translateBounds(float transX, float transY)
{
	bounds.min.x += transX;
	bounds.max.x += transX;

	bounds.min.y += transY;
	bounds.max.y += transY;
}

Bounds Entity2D::getBounds()
{
	return bounds;
}