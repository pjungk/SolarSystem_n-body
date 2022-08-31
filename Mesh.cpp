#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, std::string name, Physics physics)
{
	Mesh::name = name;
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO.Make(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();



	std::vector <glm::vec3> object;

	for (long i = 0l; i < Mesh::vertices.size(); i++)
	{
		object.push_back(glm::vec3(Mesh::vertices[i].position.x, Mesh::vertices[i].position.y, Mesh::vertices[i].position.z));
	}

	ID_num = physics.initializePosition(object, Mesh::name);

	int a = 1;
}


void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::changePosition(int vertexSize, Physics physics)
{

	float PI = acos(-1);
	float stepsize = 1.0f / 200.0f * PI;
	std::vector <Vertex> new_vertices;

	// Circle around origin
	/*
	for (int i = 0; i < vertexSize; i++)
	{
		glm::vec3 old_pos = vertices[i].position;
		float radius = sqrtf(pow(old_pos.x,2) + pow(old_pos.z, 2));
		float angle = acosf(old_pos.x/(sqrtf(pow(old_pos.x, 2) + pow(old_pos.z, 2))));
		// float angle = atanf(old_pos.x / old_pos.z) + stepsize;

		float z = old_pos.z;
		if (z < 0)
		{
			angle = -angle;
		}
		angle += stepsize;

		glm::vec3 pos = glm::vec3(radius * cosf(angle), 0.0f, radius * sinf(angle));

		new_vertices.push_back(Vertex{ pos, vertices[i].color, vertices[i].normal, vertices[i].texUV });
	}
	*/


	// Get new position of center
	glm::vec3 position = physics.updatePosition(Mesh::ID_num);
	// Get current position of center
	float sum_x = 0.0f;
	float sum_y = 0.0f;
	float sum_z = 0.0f;
	for (int i = 0; i < vertexSize; i++)
	{
		sum_x += Mesh::vertices[i].position.x;
		sum_y += Mesh::vertices[i].position.y;
		sum_z += Mesh::vertices[i].position.z;
	}
	float mean_x = sum_x / vertexSize;
	float mean_y = sum_y / vertexSize;
	float mean_z = sum_z / vertexSize;
	glm::vec3 center = glm::vec3(mean_x, mean_y, mean_z);

	// Iterate ove every vertex
	for (int i = 0; i < vertexSize; i++)
	{
		// Get position of vertex relative to the center of the sphere
		glm::vec3 distanceVector = glm::vec3(Mesh::vertices[i].position.x - center.x, Mesh::vertices[i].position.y - center.y, Mesh::vertices[i].position.z - center.z);
		// Generate new position of the vertex based on the new center
		glm::vec3 pos = glm::vec3(position.x + distanceVector.x, position.y + distanceVector.y, position.z + distanceVector.z);
		// Add new vertex position to vertices
		new_vertices.push_back(Vertex{ pos, vertices[i].normal, vertices[i].color, vertices[i].texUV });
	}

	// Update vertices
	Mesh::vertices = new_vertices;

	// Update VAO with new VBO
	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO.Make(new_vertices);
	
	// Links new VBO vertices to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
}
