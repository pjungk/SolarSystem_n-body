#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, std::string name, Physics physics)
{
	Mesh::name = name;
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;


	std::vector <Vertex> initialRotationChange;
	// Get current position of center
	glm::vec3 center = getCenter(vertices, vertices.size());

	// Iterate ove every vertex
	for (int i = 0; i < vertices.size(); i++)
	{
		Vertex newVertex = rotate(center, vertices[i].position, vertices[i], glm::vec3(1.0f, 0.0f, 0.0f), acos(-1) / 2.0f);
		// Add new vertex position to vertices
		if (name == "Sun")
		{
			initialRotationChange.push_back(Vertex{ newVertex.position, -newVertex.normal, newVertex.color, newVertex.texUV });
		}
		else
		{
			initialRotationChange.push_back(newVertex);
		}
	}
	Mesh::vertices = initialRotationChange;


	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO.Make(Mesh::vertices);
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

	PI = acos(-1);
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
	float stepsize = 1.0f / 200.0f * PI;
	std::vector <Vertex> new_vertices;

	// Get new position of center
	glm::vec3 newCenterPosition = physics.updatePosition(Mesh::ID_num);
	// Get current position of center
	glm::vec3 center = getCenter(Mesh::vertices, vertexSize);

	// Iterate ove every vertex
	for (int i = 0; i < vertexSize; i++)
	{
		glm::vec3 translatedVertex = translate(center, Mesh::vertices[i].position, newCenterPosition);
		Vertex newVertex = rotate(newCenterPosition, translatedVertex, vertices[i], physics.rotationVector[ID_num], physics.rotationVelocity[ID_num]);
		// Add new vertex position to vertices
		new_vertices.push_back(newVertex);
	}

	// Update vertices
	Mesh::vertices = new_vertices;


	// Update VAO with new VBO
	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO.Make(new_vertices);

	// Links new VBO vertices to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
}

	glm::vec3 Mesh::translate(glm::vec3 currentCenter, glm::vec3 currentVertexPosition, glm::vec3 newCenterPosition)
{
	// Get position of vertex relative to the center of the sphere
	glm::vec3 distanceVector = glm::vec3(currentVertexPosition.x - currentCenter.x, currentVertexPosition.y - currentCenter.y, currentVertexPosition.z - currentCenter.z);
	// Generate new position of the vertex based on the new center
	glm::vec3 pos = glm::vec3(newCenterPosition.x + distanceVector.x, newCenterPosition.y + distanceVector.y, newCenterPosition.z + distanceVector.z);

	return pos; // currentVertexPosition; // 
}

Vertex Mesh::rotate(glm::vec3 newCenter, glm::vec3 currentVertexPosition, Vertex currentVertex, glm::vec3 rotationVector, float rotationVelocity)
{
	float angle = rotationVelocity;
	glm::vec3 newPosition;
	glm::vec3 newNormal;

	glm::vec3 distanceVector = glm::vec3(currentVertexPosition.x - newCenter.x, currentVertexPosition.y - newCenter.y, currentVertexPosition.z - newCenter.z);

	// https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
	glm::vec3 newDistanceVector = distanceVector * cos(angle)
		+ glm::cross(rotationVector, distanceVector) * sin(angle)
		+ rotationVector * glm::dot(rotationVector, distanceVector) * (1 - cos(angle));


	newPosition = newDistanceVector + newCenter;

	newNormal = newDistanceVector; // glm::vec3(newPosition.x - newCenter.x, newPosition.y - newCenter.y, newPosition.z - newCenter.z);

	return Vertex{ newPosition, newNormal, currentVertex.color, currentVertex.texUV };
}

glm::vec3 Mesh::getCenter(std::vector <Vertex> vertices, int vertexSize)
{
	float sum_x = 0.0f;
	float sum_y = 0.0f;
	float sum_z = 0.0f;
	for (int i = 0; i < vertexSize; i++)
	{
		sum_x += vertices[i].position.x;
		sum_y += vertices[i].position.y;
		sum_z += vertices[i].position.z;
	}
	float mean_x = sum_x / vertexSize;
	float mean_y = sum_y / vertexSize;
	float mean_z = sum_z / vertexSize;

	glm::vec3 center = glm::vec3(mean_x, mean_y, mean_z);

	return center;
}
