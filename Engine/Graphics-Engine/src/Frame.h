#ifndef FRAME_H
#define FRAME_H
#include"includes.h"

struct Coordinates
{
	float u;
	float v;
};

class GENGINE_API Frame {
public:
	Coordinates frameCoords[4];
};

#endif