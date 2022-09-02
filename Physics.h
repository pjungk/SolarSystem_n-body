#ifndef PHYSICS_CLASS_H
#define PHYSICS_CLASS_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>

static class Physics
{
public:
	// Count of planets + sun
	static const int objectCount = 9;

	// Constructor
	Physics(bool scaleToReality);
	// Initialize planet(+sun) positions (and velocities)
	int initializePosition(std::vector<glm::vec3> object, std::string name);
	// Initial direction of movement (in cricle around 0,0,0 (sun))
	glm::vec3 getDirection(glm::vec3 positionVector);
	// Move the center of a planet for one timestep
	glm::vec3 updatePosition(int ID_num);
	// Get resulting force of all bodies on the planet
	glm::vec3 getForce(int ID_num);
	// Absolute distance between two objects
	long long int getDistance(glm::vec3 distance_vector);
	// Distance vector between two objects
	glm::vec3 getDistanceVector(int body1, int body2);

	// Position and velocity of planet
	static glm::vec3 positions[objectCount];
	static glm::vec3 velocities[objectCount];
	static glm::vec3 rotationVector[objectCount];
	static float rotationVelocity[objectCount];


private:
	static float timestep;
	// Needed constants to be close to real life movements
	static long long int masses[objectCount];
	static std::string IDs[objectCount];
	static float positionScalingAU[objectCount];
	static float visualToRealityScaler[objectCount];
	static float actualVelocities[objectCount];
	static float gravity_constant;
	static float astronomicalUnit;
	static bool initialized[objectCount];
	static long long int massScaling;
	// Needed Constants for Rotation
	static float rotationAxis[objectCount];
	static bool scaleToReality;
};

#endif
