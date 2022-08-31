#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

class EBO // Elements Buffer Object
{
public:
	// EBO-ID
	GLuint ID;
	// Constructor (links to indices)
	EBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif