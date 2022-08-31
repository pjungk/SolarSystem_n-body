#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

// Reads vertex and fragment shader files
std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Shader Program ID
	GLuint ID;
	// Constructor builds Shader Program from vertex and fragment shader
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
private:
	// Checks shaders compiled properly
	void compileErrors(unsigned int shader, const char* type);
};


#endif