#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Entity.h"
using namespace glm;

struct Bounds
{
	vec2 min;
	vec2 max;
	vec2 size;
};

class GENGINE_API Entity2D : public Entity {
protected:
	Bounds bounds;
public:
	Entity2D(Renderer* _renderer);
	Entity2D(Renderer* _renderer, vec2 _boundsMin, vec2 _boundsMax);
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void setBounds(Bounds _bounds);
	Bounds getBounds();
	void translateBounds(float transX, float transY);
};

#endif // !ENTITY2D_H