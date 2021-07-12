#ifndef ENTITY_H
#define ENTITY_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "TextureManager/TextureManager.h"
#include "Transform/Transform.h"

using namespace glm;

struct GENGINE_API Material
{
	vec3 diffuse = vec3(1.0f, 1.0f, 1.0f);
	vec3 specular = vec3(1.0f, 1.0f, 1.0f);
	float shininess = 0.25f;

	bool diffuseTexturesActive = false;
	bool specularTexturesActive = false;
};

class GENGINE_API Entity
{
protected:
	static Renderer* renderer;
	static TextureManager* textureManager;

	ShaderType shader = ShaderType::Main;

	float spriteTextureActive = false;
	vec3 color = vec3(0.5f, 0.5f, 0.5f);
	Material material;

	Transform* transform;

	void setUniformValues();
public:
	static void setRenderer(Renderer* _renderer);
	static void setTextureManager(TextureManager* _textureManager);

	Entity();
	Entity(vec3 _color);
	Entity(Material _material);
	Entity(vec3 _color, Material _material);
	~Entity();

	Renderer* getRenderer();
	Transform* getTransform();

	void setColor(vec3 value);
	vec3 getColor();
	void setMaterial(Material value);
	Material getMaterial();

	virtual void draw();
};

#endif // !ENTITY_H