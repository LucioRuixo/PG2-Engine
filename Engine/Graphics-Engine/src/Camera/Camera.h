#ifndef CAMERA_H
#define CAMERA_H

#include "Tools/Includes.h"
#include "Renderer/Renderer.h"
#include "Entity/Cube/Cube.h"
#include "Transform/CameraTransform/CameraTransform.h"

using namespace glm;

class GENGINE_API Camera : public Entity
{
	Renderer* renderer;
	CameraTransform* transform;
public:
	Camera(Renderer* _renderer);
	~Camera();

	CameraTransform* getTransform() override;

#pragma region Children
	vector<Entity*> getChildren() override;
	void addChild(Entity* child) override;
	void removeChild(Entity* child) override;
#pragma endregion

#pragma region Parent
	void setParent(Entity* _parent) override;
	Entity* getParent() override;
#pragma endregion
};

#endif // !CAMERA_H