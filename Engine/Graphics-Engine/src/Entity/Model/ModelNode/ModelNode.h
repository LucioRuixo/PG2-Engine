#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include "Tools/Includes.h"
#include "Entity/Plane/Plane.h"
#include "Entity/Model/Mesh/Mesh.h"
#include "Transform/ModelNodeTransform/ModelNodeTransform.h"

using namespace std;

struct CollisionBoxEdges
{
	vec3 minEdge = vec3(0.0f);
	vec3 maxEdge = vec3(0.0f);
};

class GENGINE_API ModelNode : public Entity
{
	string name;
	bool isRoot;

	CollisionBoxEdges collisionBoxEdges;
	vector<vec3> collisionBoxVertices;

	ModelNodeTransform* transform;

	vector<Mesh*> meshes;

	void setUpCollisionBox();
	vector<vec3> generateCollisonBoxVertices(CollisionBoxEdges edges);
	CollisionBoxEdges generateCollisonBoxEdges(vector<vec3> vertices);

	void processBSP(bool shouldBeDrawn, vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes);
	void drawChildrenAsBSPNode(bool shouldBeDrawn, vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes);
public:
	ModelNode(string _name, bool _isRoot, vector<Mesh*> _meshes, vector<Entity*> _children);
	~ModelNode();

	void updateModels(mat4 otherModel) override;

	string getName();
	bool getIsRoot();
	CollisionBoxEdges getRawCollisionBox();
	CollisionBoxEdges getCollisionBox();
	vector<vec3> getCollisionBoxVertices();
	ModelNodeTransform* getTransform() override;

#pragma region Children
	void addChild(Entity* child) override;
	void removeChild(Entity* child) override;
#pragma endregion

	void drawMeshes();
	void draw() override;
	void drawAsBSPNode(vec3 cameraPosition, vector<Plane*> planes, bool drawPlanes);
};

#endif // !MODEL_NODE_H