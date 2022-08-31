#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Important, that names match names in vertex shader
// Imports position from vertex shader
in vec3 crntPos;
// Imports normal from vertex shader
in vec3 Normal;
// Imports color from vertex shader
in vec3 color;
// Imports texture coordinates from vertex shader
in vec2 texCoord;



// Gets texture units from main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets color of the light from main function
uniform vec4 lightColor;
// Gets position of the light from main function
uniform vec3 lightPos;
// Gets position of the camera from main function
uniform vec3 camPos;


vec4 pointLight()
{	
	// ambient lighting
	float ambient = 0.2f;

	vec3 lightVec = lightPos - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 0.1;
	float b = 0.1;
	float inten = 1.0f; // / (a * dist * dist + b * dist + 1.0f);


	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);


	// specular lighting
	float specularLight = 0.10f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec3 testLight()
{	
	// ambient lighting
	float ambient = 0.2f;

	vec3 lightVec = lightPos - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 0.1;
	float b = 0.1;
	float inten = 3.0f; // / (a * dist * dist + b * dist + 1.0f);


	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);


	// specular lighting
	float specularLight = 0.10f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return normal;
}

void main()
{
	// outputs final color
	FragColor = pointLight();
	vec3 asdf = testLight();
	//FragColor = vec4(asdf, 1.0f);
}