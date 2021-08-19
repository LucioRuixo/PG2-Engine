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

	Entity* parent = NULL;
	vector<Entity*> children;

	void setUniformValues();
public:
	static void setRenderer(Renderer* _renderer);
	static void setTextureManager(TextureManager* _textureManager);

	Entity();
	Entity(vector<Entity*> _children);
	Entity(vec3 _color);
	Entity(Material _material);
	Entity(vec3 _color, Material _material);
	~Entity();

	Renderer* getRenderer();
	Transform* getTransform();

#pragma region Rendering
	void setColor(vec3 value);
	vec3 getColor();
	void setMaterial(Material value);
	Material getMaterial();
#pragma endregion

#pragma region Children
	vector<Entity*> getChildren();
	void addChild(Entity* child);
	void addChildren(vector<Entity*> newChildren);
	void removeChild(Entity* child);
#pragma endregion

#pragma region Parent
	void setParent(Entity* _parent);
	Entity* getParent();
#pragma endregion

	virtual void draw();
};

#endif // !ENTITY_H