#include "Sphere.h"


// Constructor defining the position and detail degree
Sphere::Sphere(glm::vec3 centerPosition, float radius, int sectorCount, int stackCount)
{
	Sphere::centerPosition = centerPosition;
	Sphere::radius = radius;
	Sphere::sectorCount = sectorCount;
	Sphere::stackCount = stackCount;
}

// Generates vertices of the Sphere
std::vector <Vertex> Sphere::getVertices(bool invertedNormals)
{
	std::vector<glm::vec3>vertices;
	std::vector<glm::vec3>normals;
	std::vector<glm::vec2>texCoords;
	glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);


	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;

	float sectorStep = 2 * PI_sphere / sectorCount;
	float stackStep = PI_sphere / stackCount;

	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI_sphere / 2 - i * stackStep;		// starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);					// r * cos(u)
		z = radius * sinf(stackAngle);					// r * sin(u)

		// add (sectorCount+1) vertices per stackthe first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertices.push_back(glm::vec3(x + centerPosition.x, y + centerPosition.y, z + centerPosition.z));

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			if (invertedNormals)
			{
				normals.push_back(glm::vec3(-nx, -ny, -nz));
			}
			else
			{
				normals.push_back(glm::vec3(nx, ny, nz));
			}

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			texCoords.push_back(glm::vec2(s, t));
		}
	}


	std::vector<Vertex> sphereVertices;

	for (int i = 0; i < vertices.size(); i++)
	{
		sphereVertices.push_back(Vertex{ vertices[i], normals[i], color, texCoords[i] });
	}

	return sphereVertices;
}

// Generates Indices of the sphere
std::vector <GLuint> Sphere::getIndices()
{
	// generate CCW index list of sphere triangles
	// k1--k1+1
	// |  / |
	// | /  |
	// k2--k2+1
	std::vector<GLuint> sphereIndices;
	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				sphereIndices.push_back(k1);
				sphereIndices.push_back(k2);
				sphereIndices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				sphereIndices.push_back(k1 + 1);
				sphereIndices.push_back(k2);
				sphereIndices.push_back(k2 + 1);
			}
		}
	}

	return sphereIndices;
}
