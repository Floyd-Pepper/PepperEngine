#pragma once
#include "Mesh.h"

class Plane : public Mesh
{
public:
	//Plane();
	Plane(Shader& shader);
	~Plane();
};