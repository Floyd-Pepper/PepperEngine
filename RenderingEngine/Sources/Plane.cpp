#include "Plane.h"
#include <string>

Plane::Plane(unsigned int xSegments, unsigned int ySegments, unsigned int textureRepeatNumber)
{
	bool oddRow = false;

	float dX = 1.0f / xSegments;
	float dY = 1.0f / ySegments;
	std::vector<glm::vec3> Positions;
	std::vector<glm::vec2> UV;
	std::vector<glm::vec3> Normals;
	std::vector<int> Indices;


	for (int y = 0; y <= ySegments; ++y)
	{
		for (int x = 0; x <= xSegments; ++x)
		{
			Positions.push_back(glm::vec3(dX * x * 2.0f - 1.0f, dY * y * 2.0f - 1.0f, 0.0f));
			UV.push_back(glm::vec2((dX * x) * textureRepeatNumber, (1.0f - y * dY) * textureRepeatNumber));
			Normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}

	for (int y = 0; y < ySegments; ++y)
	{
		if (!oddRow) 
		{
			for (int x = 0; x <= xSegments; ++x)
			{
				Indices.push_back(y       * (xSegments + 1) + x);
				Indices.push_back((y + 1) * (xSegments + 1) + x);
			}
		}
		else
		{
			for (int x = xSegments; x >= 0; --x)
			{
				Indices.push_back((y + 1) * (xSegments + 1) + x);
				Indices.push_back(y       * (xSegments + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	_Topology = TRIANGLE_STRIP;
	FillDataStructure(Positions, UV, Normals, Indices);
	ConfigureMesh();
}

Plane::Plane()
{
	_VerticesNumber = 6;

	std::vector<glm::vec3> positions = {
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f,  0.5f, -0.5f),
		glm::vec3(0.5f,  0.5f, -0.5f),
		glm::vec3(-0.5f,  0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f)
	};

	std::vector<glm::vec2> UV = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)
	};

	std::vector<glm::vec3> normals = {
		glm::vec3(0.0f,  0.0f, -1.0f),
		glm::vec3(0.0f,  0.0f, -1.0f),
		glm::vec3(0.0f,  0.0f, -1.0f),
		glm::vec3(0.0f,  0.0f, -1.0f),
		glm::vec3(0.0f,  0.0f, -1.0f),
		glm::vec3(0.0f,  0.0f, -1.0f),
	};

	FillDataStructure(positions, UV, normals);
	ConfigureMesh();
}

Plane::~Plane()
{
}