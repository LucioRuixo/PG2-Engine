#ifndef ENTITY_H
#define ENTITY_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "TextureManager/TextureManager.h"
#include "Transform/Transform.h"

using namespace glm;

const int VERTEX_ELEMENTS = 3;
const int VERTEX_LENGTH = 8;

struct GENGINE_API CollisionBoxEdges
{
	vec3 minEdge = vec3(0.0f);
	vec3 maxEdge = vec3(0.0f);
};

struct GENGINE_API Material
{
	vec3 diffuse = vec3(1.0f, 1.0f, 1.0f);
	vec3 specular = vec3(1.0f, 1.0f, 1.0f);
	float shininess = 0.25f;
	float alpha = 1.0f;

	bool diffuseTexturesActive = false;
	bool specularTexturesActive = false;
};

class GENGINE_API Entity
{
	static vector<Entity*> entities;
	static vector<Entity*> renderizableEntities;

protected:
	static Renderer* renderer;
	static TextureManager* textureManager;

	//Plane
	//----------
	static bool planeRenderingDataInitialized;
	static vector<vec3> planeVertexPositions;
	//----------

	//Cube
	//----------
	static bool cubeRenderingDataInitialized;
	static vector<vec3> cubeVertexPositions;
	//----------

	ShaderType shader = ShaderType::Main;
	bool renderizable = true;
	bool shouldBeDrawn = true;

	float spriteTextureActive = false;
	vec3 color = vec3(0.5f, 0.5f, 0.5f);
	Material material;

	Transform* transform;

	Entity* parent = NULL;
	vector<Entity*> children;

	void setUniformValues();

#pragma Collision Box
	vector<vec3> collisionVertices;

	vector<vec3> transformVertices(vector<vec3> vertices);
	vector<vec3> generateCBVertices(CollisionBoxEdges edges);
	CollisionBoxEdges generateCBEdges(vector<vec3> vertices);
	vector<vec3> calculateCollisionVertices(vector<vec3> vertices);

	virtual vector<vec3> getTransformedVertices(vector<vec3> vertices);
	virtual CollisionBoxEdges getTransformedEdges(vector<vec3> vertices);
#pragma endregion

public:
	static vector<Entity*> getEntities();
	static vector<Entity*> getRenderizableEntities();
	static void setRenderer(Renderer* _renderer);
	static void setTextureManager(TextureManager* _textureManager);

	Entity(bool _renderizable = true);
	Entity(vector<Entity*> _children, bool _renderizable = true);
	Entity(vec3 _color, bool _renderizable = true);
	Entity(Material _material, bool _renderizable = true);
	Entity(vec3 _color, Material _material, bool _renderizable = true);
	~Entity();

	void initialize(bool _renderizable);
	
	Renderer* getRenderer();
	virtual Transform* getTransform();
	virtual void updateModels(mat4 otherModel);

#pragma region Rendering
	void setShouldBeDrawn(bool _shouldBeDrawn);
	bool getShouldBeDrawn();
	void setColor(vec3 value);
	vec3 getColor();
	void setMaterial(Material value);
	Material getMaterial();
#pragma endregion

#pragma region Children
	virtual vector<Entity*> getChildren();
	virtual void addChild(Entity* child);
	virtual void removeChild(Entity* child);
#pragma endregion

#pragma region Parent
	virtual void setParent(Entity* _parent);
	virtual Entity* getParent();
#pragma endregion

#pragma Collision Box
	virtual vector<vec3> getCollisionVertices() = 0;
#pragma endregion

	virtual void draw();
};

#endif // !ENTITY_H