#ifndef CAMERA_H
#define CAMERA_H

#include "../Tools/Includes.h"
#include "../Renderer/Renderer.h"

class GENGINE_API Camera
{
	Renderer* renderer;
public:
	Camera(Renderer* renderer);
	~Camera();
	void translate(float x, float y, float z);
	void translate(glm::vec3 translation);
};

#endif // !CAMERA_H