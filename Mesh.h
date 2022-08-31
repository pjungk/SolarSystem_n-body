#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"
#include "Physics.h"

class Mesh
{
public:
	std::string name;
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	// Store VAO and VBO in public so they can be used further
	VAO VAO;
	VBO VBO;
	// Num of object (planet)
	int ID_num;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, std::string name, Physics physics);

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);
	// Changes the position of the planet (and all their vertices)
	void changePosition(int vertexSize, Physics physics);
	// Test function for changing the position
	//void changePosition2(int vertexSize);
};

#endif