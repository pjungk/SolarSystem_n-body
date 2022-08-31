#version 330 core

// Vertex Position/Coordinates
layout (location = 0) in vec3 aPos;
// Normals
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


// Outputs current position to the fragment shader
out vec3 crntPos;
// Outputs normal to the fragment shader
out vec3 Normal;
// Outputs color to the fragment shader
out vec3 color;
// Outputs texture coordinates to the fragment shader
out vec2 texCoord;


// Imports camera matrix from the main function
uniform mat4 camMatrix;
// Imports model matrix from the main function
uniform mat4 model;


void main()
{
	// Calculates current position
	crntPos = aPos; // vec3(model * vec4(aPos, 1.0f)); // 
	// Assigns normal from Vertex Data to "Normal" for the fragment shader
	Normal = aNormal;
	//  Assigns colors from Vertex Data to "color" for the fragment shader
	color = aColor;
	//  Assigns texture coordinates from Vertex Data to "texCoord" for the fragment shader
	texCoord = aTex;
	
	// Outputs the position/coordinates of all vertices (gl_Position is automatically recognized)
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}