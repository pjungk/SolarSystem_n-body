#include "Physics.h"


// Initialize scales
float Physics::astronomicalUnit = 150000000000.0f;
float Physics::positionScalingAU[Physics::objectCount] = { 0.0f, 0.4f, 0.7f, 1.0f, 1.5f, 5.2f, 9.5f, 19.2f, 30.1f };
float Physics::visualToRealityScaler[Physics::objectCount] = {  };
float Physics::actualVelocities[Physics::objectCount] = { 0.0f, 47360.0f, 35020.0f, 29780.0f, 24070.0f, 13070.0f, 9680.0f, 6800.0f, 5430.0f };
// Initialize needed constants
long long int Physics::massScaling = 1e15;				// 1.98892e15l			// 4.875e9l				// 1.898e12l
long long int Physics::masses[Physics::objectCount] = { 1.98892e15l, 3.301e8l, 4.875e9l, 5.972e9l, 6.39e8l, 1.898e12l, 5.6834e11l, 8.681e10l, 1.024e11l };
std::string Physics::IDs[Physics::objectCount] = { "Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };
glm::vec3 Physics::positions[Physics::objectCount] = {};
glm::vec3 Physics::velocities[Physics::objectCount] = {};
float Physics::gravity_constant = 6.67430e-11;
bool Physics::initialized[Physics::objectCount] = { false, false, false, false, false, false, false, false, false };


// Constructor (initializing position and velocity variable)
Physics::Physics()
{
	for (int i = 0; i < Physics::objectCount; i++)
	{
		positions[i] = glm::vec3(0.0f, 0.0f, 0.0f);
		velocities[i] = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

// Initialize position from coordinates given in mesh
int Physics::initializePosition(std::vector<glm::vec3> object, std::string name)
{
	int ID_num = -1;

	// Check for object using name by iterating all objects // I know it's disgusting...
	for (int i = 0; i < Physics::objectCount; i++)
	{
		if (IDs[i] == name)
		{
			float sum_x = 0.0f;
			float sum_y = 0.0f;
			float sum_z = 0.0f;

			int test = object.size();

			for (int j = 0; j < object.size(); j++)
			{
				sum_x += object[j].x;
				sum_y += object[j].y;
				sum_z += object[j].z;
			}
			// Get center coordinates of sphere
			float mean_x = sum_x / object.size();
			float mean_y = sum_y / object.size();
			float mean_z = sum_z / object.size();

			// Scale coordinates from graphic coordinates in mesh to real world
			if (sqrt(pow(mean_x, 2) + pow(mean_y, 2) + pow(mean_z, 2)) == 0)
			{
				visualToRealityScaler[i] = 0.0f;
			}
			else
			{
				visualToRealityScaler[i] = positionScalingAU[i] * float(astronomicalUnit) / sqrt(pow(mean_x, 2) + pow(mean_y, 2) + pow(mean_z, 2));
			}
			positions[i] = glm::vec3(mean_x, mean_y, mean_z) * visualToRealityScaler[i];
			// Initialize velocities using real world data
			velocities[i] = getDirection(positions[i]) * actualVelocities[i];

			ID_num = i;
			initialized[i] = true;
			break;
		}
	}

	return ID_num;
}

// Get direction of initial velocity
glm::vec3 Physics::getDirection(glm::vec3 positionVector)
{
	glm::vec3 standardizedDirection;
	// Get vector perpendicular to solar system "disk"
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	// Get vector perpendicular to position vector and up vector for the movement direction
	glm::vec3 direction = glm::vec3(up.y * positionVector.z - up.z * positionVector.y,
		up.z * positionVector.x - up.x * positionVector.z,
		up.x * positionVector.y - up.y * positionVector.x);

	standardizedDirection = glm::normalize(direction);

	return standardizedDirection;
}


glm::vec3 Physics::updatePosition(int ID_num)
{
	// Get force exerted on the object and calculate the resulting acceleration
	glm::vec3 force = getForce(ID_num);

	float accel_x = force.x / masses[ID_num] * massScaling;
	float accel_y = force.y / masses[ID_num] * massScaling;
	float accel_z = force.z / masses[ID_num] * massScaling;

	float timestepf = static_cast<float> (timestep);


	// Calculate new positions
	float new_x = 1.0f / 2.0f * accel_x * pow(float(timestepf), 2) + float(velocities[ID_num].x) * float(timestepf) + positions[ID_num].x;
	float new_y = 1.0f / 2.0f * accel_y * pow(float(timestepf), 2) + float(velocities[ID_num].y) * float(timestepf) + positions[ID_num].y;
	float new_z = 1.0f / 2.0f * accel_z * pow(float(timestepf), 2) + float(velocities[ID_num].z) * float(timestepf) + positions[ID_num].z;

	// Calculate new velocities
	float new_vx = accel_x * timestepf + velocities[ID_num].x;
	float new_vy = accel_y * timestepf + velocities[ID_num].y;
	float new_vz = accel_z * timestepf + velocities[ID_num].z;

	// Set new positions and velocities
	positions[ID_num] = glm::vec3(new_x, new_y, new_z);
	velocities[ID_num] = glm::vec3(new_vx, new_vy, new_vz);

	return positions[ID_num] / visualToRealityScaler[ID_num];
}


glm::vec3 Physics::getForce(int ID_num)
{
	// Iterate through celestial bodies and get exerted forces
	glm::vec3 summedForce = glm::vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < objectCount; i++)
	{
		if (i != ID_num && initialized[i])
		{
			// Get gravity force
			glm::vec3 distance_vector = getDistanceVector(i, ID_num);
			float force_value = gravity_constant * masses[i] * masses[ID_num] * pow(getDistance(distance_vector), -2); // * pow(massScaling,2)

			summedForce.x += float(force_value) * float(distance_vector.x) / sqrt(pow(getDistance(distance_vector), 2));
			summedForce.y += float(force_value) * float(distance_vector.y) / sqrt(pow(getDistance(distance_vector), 2));
			summedForce.z += float(force_value) * float(distance_vector.z) / sqrt(pow(getDistance(distance_vector), 2));
		}
		else if (i == ID_num)
		{
			//std::cout << Physics::IDs[i] << " does not exert a force on " << Physics::IDs[i] << std::endl;
		}
		else
		{
			//std::cout << Physics::IDs[i] << " might not be initialized!" << std::endl;
		}
	}

	return summedForce;
}

long long int Physics::getDistance(glm::vec3 distance_vector)
{
	// Absolute length of distance vector (or any vector really)
	float distance = sqrt(pow(distance_vector.x, 2) + pow(distance_vector.y, 2) + pow(distance_vector.z, 2));

	return distance;
}

glm::vec3 Physics::getDistanceVector(int body1, int body2)
{
	// Get vector between two objects (direction 2 -> 1)
	glm::vec3 pos_1 = positions[body1];
	glm::vec3 pos_2 = positions[body2];

	glm::vec3 distance_vector = glm::vec3(pos_1.x - pos_2.x, pos_1.y - pos_2.y, pos_1.z - pos_2.z);

	return distance_vector;
}