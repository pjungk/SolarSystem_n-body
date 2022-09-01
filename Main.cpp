#include "Mesh.h"
#include "Sphere.h"


const unsigned int width = 1500;
const unsigned int height = 800;
const float PI = acosf(-1);

const int sectorCount = 30;
const int stackCount = 30;


int main()
{
	float scaledPosition[9] = { 0.0f, 0.4f, 0.7f, 1.0f, 1.5f, 5.2f, 9.5f, 19.2f, 30.1f };
	float scaleFactor = 20.0f;

	Sphere sunSphere = Sphere(glm::vec3(scaledPosition[0]*scaleFactor, 0.0f, 0.0f), 7.0f, sectorCount, stackCount);
	std::vector<Vertex> sunVertices = sunSphere.getVertices(true);
	std::vector<GLuint> sunIndices = sunSphere.getIndices();

	Sphere mercurySphere = Sphere(glm::vec3(scaledPosition[1] * scaleFactor, 0.0f, 0.0f), 0.48f, sectorCount, stackCount); // x-pos: 4.0f
	std::vector<Vertex> mercuryVertices = mercurySphere.getVertices(false);
	std::vector<GLuint> mercuryIndices = mercurySphere.getIndices();

	Sphere venusSphere = Sphere(glm::vec3(scaledPosition[2] * scaleFactor, 0.0f, 0.0f), 1.2f, sectorCount, stackCount); // x-pos: 7.0f
	std::vector<Vertex> venusVertices = venusSphere.getVertices(false);
	std::vector<GLuint> venusIndices = venusSphere.getIndices();

	Sphere earthSphere = Sphere(glm::vec3(scaledPosition[3] * scaleFactor, 0.0f, 0.0f), 1.3f, sectorCount, stackCount); // x-pos: 10.0f
	std::vector<Vertex> earthVertices = earthSphere.getVertices(false);
	std::vector<GLuint> earthIndices = earthSphere.getIndices();

	Sphere marsSphere = Sphere(glm::vec3(scaledPosition[4] * scaleFactor, 0.0f, 0.0f), 0.7f, sectorCount, stackCount); // x-pos: 15.0f
	std::vector<Vertex> marsVertices = marsSphere.getVertices(false);
	std::vector<GLuint> marsIndices = marsSphere.getIndices();

	Sphere jupiterSphere = Sphere(glm::vec3(scaledPosition[5] * scaleFactor, 0.0f, 0.0f), 7.0f, sectorCount, stackCount); // x-pos: 52.0f
	std::vector<Vertex> jupiterVertices = jupiterSphere.getVertices(false);
	std::vector<GLuint> jupiterIndices = jupiterSphere.getIndices();

	Sphere saturnSphere = Sphere(glm::vec3(scaledPosition[6] * scaleFactor, 0.0f, 0.0f), 6.0f, sectorCount, stackCount); // x-pos: 95.0f
	std::vector<Vertex> saturnVertices = saturnSphere.getVertices(false);
	std::vector<GLuint> saturnIndices = saturnSphere.getIndices();

	Sphere uranusSphere = Sphere(glm::vec3(scaledPosition[7] * scaleFactor, 0.0f, 0.0f), 3.0f, sectorCount, stackCount); // x-pos: 192.0f
	std::vector<Vertex> uranusVertices = uranusSphere.getVertices(false);
	std::vector<GLuint> uranusIndices = uranusSphere.getIndices();

	Sphere neptuneSphere = Sphere(glm::vec3(scaledPosition[8] * scaleFactor, 0.0f, 0.0f), 3.0f, sectorCount, stackCount); // x-pos: 301.0f
	std::vector<Vertex> neptuneVertices = neptuneSphere.getVertices(false);
	std::vector<GLuint> neptuneIndices = neptuneSphere.getIndices();

	Sphere backgroundSphere = Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1000.0f, sectorCount, stackCount);
	std::vector<Vertex> backgroundVertices = backgroundSphere.getVertices(false);
	std::vector<GLuint> backgroundIndices = backgroundSphere.getIndices();


	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Solar System", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	std::vector<Texture> sunTexture = { Texture("Textures/sun_sphere.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };
	std::vector<Texture> mercuryTexture = { Texture("Textures/mercury_sphere.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };
	std::vector<Texture> venusTexture = { Texture("Textures/venus_sphere_surf.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };
	std::vector<Texture> earthTexture = { Texture("Textures/earth_sphere.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };
	std::vector<Texture> marsTexture = { Texture("Textures/mars_sphere.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };
	std::vector<Texture> jupiterTexture = { Texture("Textures/jupiter_sphere.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };
	std::vector<Texture> saturnTexture = { Texture("Textures/saturn_sphere.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };
	std::vector<Texture> uranusTexture = { Texture("Textures/uranus_sphere.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };
	std::vector<Texture> neptuneTexture = { Texture("Textures/neptune_sphere.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };
	std::vector<Texture> backgroundTexture = { Texture("Textures/night_sky_sphere_hd.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE), };


	static Physics physics;

	// Possible names: { "Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" }
	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	Mesh sun(sunVertices, sunIndices, sunTexture, "Sun", physics);
	Mesh mercury(mercuryVertices, mercuryIndices, mercuryTexture, "Mercury", physics);
	Mesh venus(venusVertices, venusIndices, venusTexture, "Venus", physics);
	Mesh earth(earthVertices, earthIndices, earthTexture, "Earth", physics);
	Mesh mars(marsVertices, marsIndices, marsTexture, "Mars", physics);
	Mesh jupiter(jupiterVertices, jupiterIndices, jupiterTexture, "Jupiter", physics);
	Mesh saturn(saturnVertices, saturnIndices, saturnTexture, "Saturn", physics);
	Mesh uranus(uranusVertices, uranusIndices, uranusTexture, "Uranus", physics);
	Mesh neptune(neptuneVertices, neptuneIndices, neptuneTexture, "Neptune", physics);
	Mesh background(backgroundVertices, backgroundIndices, backgroundTexture, "Sun", physics);


	// Handle lighting
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = sunSphere.centerPosition; // glm::vec3(0.0f, 0.0f, 0.0f); // 
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 300.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 1800.0f);


		// Draws different meshes
		sun.Draw(shaderProgram, camera);
		mercury.Draw(shaderProgram, camera);
		venus.Draw(shaderProgram, camera);
		earth.Draw(shaderProgram, camera);
		mars.Draw(shaderProgram, camera);
		jupiter.Draw(shaderProgram, camera);
		saturn.Draw(shaderProgram, camera);
		uranus.Draw(shaderProgram, camera);
		neptune.Draw(shaderProgram, camera);
		background.Draw(shaderProgram, camera);


		// Change position of planets
		//sun.changePosition(sunVertices.size(), physics); // Breaks stuff
		mercury.changePosition(mercuryVertices.size(), physics);
		venus.changePosition(venusVertices.size(), physics);
		earth.changePosition(earthVertices.size(), physics);
		mars.changePosition(marsVertices.size(), physics);
		jupiter.changePosition(jupiterVertices.size(), physics);
		saturn.changePosition(saturnVertices.size(), physics);
		uranus.changePosition(uranusVertices.size(), physics);
		neptune.changePosition(neptuneVertices.size(), physics);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}