#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	// Texture ID
	GLuint ID;
	// Texture type ("diffuse" vs "specular")
	const char* type;
	GLuint unit;

	// Texture Constructor
	Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

	// Assigns texture to fragment shader uniform
	void texUnit(Shader& shader, const char* uniform, GLuint unit);


	void Bind();
	void Unbind();
	void Delete();
};

#endif