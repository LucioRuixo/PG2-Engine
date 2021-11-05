#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <string>
#include <vector>
#include "Tools/Includes.h"
#include "Entity/Plane/Plane.h"
#include "Entity/Model/Mesh/Mesh.h"
#include "Transform/ModelNodeTransform/ModelNodeTransform.h"

using namespace std;

struct CollisionBox
{
	vec3 minEdge = vec3(0.0f);
	vec3 maxEdge = vec3(0.0f);
};

class GENGINE_API ModelNode : public Entity
{
	string name;
	bool isRoot;

	CollisionBox collisionBox;
	ModelNodeTransform* transform;

	vector<Mesh*> meshes;

	void generateCollisonBox();
	void processBSP(bool shouldBeDrawn, vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes);
	void drawChildrenAsBSPNode(bool shouldBeDrawn, vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes);
public:
	ModelNode(string _name, bool _isRoot, vector<Mesh*> _meshes, vector<Entity*> _children);
	~ModelNode();

	void updateModels(mat4 otherModel) override;

	string getName();
	bool getIsRoot();
	CollisionBox getRawCollisionBox();
	CollisionBox getCollisionBox();
	vec3* getCollisionBoxVertices();
	ModelNodeTransform* getTransform() override;

	void drawMeshes();
	void draw() override;
	void drawAsBSPNode(vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes);
};

#endif // !MODEL_NODE_H