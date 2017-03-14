#pragma once
#include "Mesh.h"

class Plane : public Mesh
{
public:
	Plane();
	Plane(unsigned int xSegments, unsigned int ySegments, unsigned int textureRepeatNumber = 1);
	~Plane();
};