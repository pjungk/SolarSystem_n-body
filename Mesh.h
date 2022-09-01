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
	float PI;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, std::string name, Physics physics);

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);
	// Changes the position and rotation of the planet (and all their vertices)
	void changePosition(int vertexSize, Physics physics);
	// Translates a vertex based on the physics calculation
	glm::vec3 translate(glm::vec3 currentCenter, glm::vec3 currentVertexPosition, glm::vec3 newCenterPosition);
	// Rotates a vertex based on the physics timestep and a arbitrary angle
	Vertex rotate(glm::vec3 newCenter, glm::vec3 currentVertexPosition, Vertex currentVertex, glm::vec3 rotationVector, float rotationVelocity);
	// Get position of planet center
	glm::vec3 getCenter(std::vector<Vertex> vertices, int vertexSize);
};

#endif