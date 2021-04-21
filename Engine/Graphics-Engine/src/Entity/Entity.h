#ifndef ENTITY_H
#define ENTITY_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Transform/Transform.h"

using namespace glm;

struct Material
{
	vec3 ambient = vec3(0.1f, 0.1f, 0.1f);
	vec3 diffuse = vec3(1.0f, 1.0f, 1.0f);
	vec3 specular = vec3(1.0f, 1.0f, 1.0f);
	float shininess = 0.25f;
};

const int VERTEX_BUFFER_SIZE = 396;

class GENGINE_API Entity
{
	void construct(Renderer *_renderer);
protected:
	float vertexBuffer[VERTEX_BUFFER_SIZE];

	float textureActive = false;
	vec3 color = vec3(0.5f, 0.5f, 0.5f);
	Material material;

	ModelMatrixData modelMatrix;
	Renderer* renderer;

	void updateModelMatrix();
public:
	Transform* transform;

	Entity(Renderer* _renderer);
	Entity(Renderer* _renderer, vec3 _color);
	Entity(Renderer* _renderer, Material _material);
	Entity(Renderer* _renderer, vec3 _color, Material _material);
	~Entity();

	Renderer* getRenderer();
	mat4 getModel();

	virtual void setPosition(float x, float y, float z);
	virtual void translate(float x, float y, float z);
	void setRotation(float x, float y, float z);
	//void setRotationX(float x);
	//void setRotationY(float y);
	//void setRotationZ(float z);
	virtual void setScale(float x, float y, float z);

	void setColor(vec3 value);
	vec3 getColor();
	void setMaterial(Material value);
	Material getMaterial();

	void draw();
};

#endif // !ENTITY