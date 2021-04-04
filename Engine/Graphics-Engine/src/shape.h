#ifndef SHAPE_H
#define SHAPE_H

#include "Includes.h"
#include "Entity2D.h"

class GENGINE_API Shape : public Entity2D{
private:
	int type;
	//int vertexBufferSize;
public:
	Shape(Renderer* _renderer, int _type);
	~Shape();
	void setBufferData();
};

#endif // !SHAPE_H