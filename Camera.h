#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:
	// Stores the vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Centers mouse in the window on the first left click to prevent the camera from jumping
	bool firstClick = true;

	// Stores the width and height of the window
	int width;
	int height;

	// Speed and sensitivity of camera movement
	float speed = 0.3f;
	float sensitivity = 100.0f;

	// Constructor with initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates camera matrix
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports camera matrix to shader
	void Matrix(Shader& shader, const char* uniform);
	// Get and handle camera inputs
	void Inputs(GLFWwindow* window);
};
#endif