#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include "Tools/Includes.h"
#include "Entity/Plane/Plane.h"
#include "Entity/Model/Mesh/Mesh.h"
#include "Transform/ModelNodeTransform/ModelNodeTransform.h"

using namespace std;

class GENGINE_API ModelNode : public Entity
{
	string name;
	bool isRoot;

	ModelNodeTransform* transform;
	vector<Mesh*> meshes;

#pragma BSP
	void processBSP(vec3 cameraPosition, vector<Plane*> planes);
	void drawChildrenAsBSPNode(vec3 cameraPosition, vector<Plane*> planes);
#pragma endregion

protected:
#pragma Collision Box
	vector<vec3> collisionBoxVertices;

	//vector<vec3> generateCollisonBoxVertices(CollisionBoxEdges edges) override;
	//CollisionBoxEdges generateCollisonBoxEdges(vector<vec3> vertices) override;

	vector<vec3> getTransformedVertices();
	CollisionBoxEdges getTransformedEdges();
#pragma endregion

public:
	ModelNode(string _name, bool _isRoot, vector<Mesh*> _meshes, vector<Entity*> _children);
	~ModelNode();

	void updateModels(mat4 otherModel) override;

	string getName();
	bool getIsRoot();

#pragma region Children
	void addChild(Entity* child) override;
	void removeChild(Entity* child) override;
	ModelNodeTransform* getTransform() override;
#pragma endregion

#pragma Collision Box
	vector<vec3> getCollisionVertices() override;
#pragma endregion

#pragma region BSP
	void drawAsBSPNode(vec3 cameraPosition, vector<Plane*> planes);
#pragma endregion

	void drawMeshes();
	void draw() override;
};

#endif // !MODEL_NODE_H