#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO // Vertex Array Object
{
public:
	// VAO-ID
	GLuint ID;
	// Constructor
	VAO();

	// Links a VBO Attribute to VAO
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();
};

#endif