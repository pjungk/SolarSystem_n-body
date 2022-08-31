#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

// Structure for vertices input order used in the meshes
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};



class VBO // Vertex Buffer Object
{
public:
	// VBO-ID
	GLuint ID;
	// Constructor
	VBO();

	void Bind();
	void Unbind();
	void Delete();
	// Links VBO to vertices
	void Make(std::vector<Vertex>& vertices);
};

#endif