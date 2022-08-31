#ifndef GEOMETRY_SPHERE_H
#define GEOMETRY_SPHERE_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "VBO.h"

class Sphere
{
public:
	// "Get" PI
	const float PI_sphere = acosf(-1);
	// Create variable for the center position of the Sphere
	glm::vec3 centerPosition;
	// Degree of detail and radius
	int sectorCount;
	int stackCount;
	float radius;

	// Constructor of the Sphere
	Sphere(glm::vec3 centerPosition, float radius, int sectorCount, int stackCount);
	// Creates the Vertices, with variable for inverted normals (so the sun is "illuminated")
	std::vector <Vertex> getVertices(bool invertedNormals);
	// Defines the triangle connections of the vertices
	std::vector <GLuint> getIndices();

};

#endif
