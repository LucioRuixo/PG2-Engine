#include "Camera.h"

Camera::Camera(Renderer* _renderer)
{
	renderer = _renderer;

	transform = new CameraTransform(renderer);
}

Camera::~Camera() { if (transform) delete transform; }

CameraTransform * Camera::getTransform() { return transform; }