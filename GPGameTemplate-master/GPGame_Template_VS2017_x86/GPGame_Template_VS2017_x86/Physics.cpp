#include <iostream>
#include <vector>
using namespace std;

// Helper graphic libraries
#include <GL/glew.h>
#include <chrono> 

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
#include "Particles.cpp"



class Physics {
private:
	// Acceleration for the
	const glm::vec3 acceleration = glm::vec3(0.0f, -0.0181f, 0.0f);

	// Use chrono for decimal time points
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;

public:
	// Has touched ground
	bool Insky = false;

	// Pointer to explosion emitter
	ParticleEmitter explosion;

	// Required in class to prevent already defined error
	std::chrono::steady_clock::time_point t0 = Time::now();

	// define inits
	glm::vec3 position;
	glm::vec3 velocity;
	float mass = 2.0f;	// Default mass of 2 units

	void calcPosition(glm::vec3 cur_pos) {
		if (Insky)
			return;
		

		// calc time since start
		auto t1 = Time::now();	// grab current time
		fsec fs = t1 - t0;		// find difference

		// output difference in seconds
		std::cout << fs.count() << "s\n";

		// distance travelled
		glm::vec3 newDistance = ((acceleration * (fs.count() * fs.count())) * 0.5f);

		// As it's gravity, remove the travelled distance from current
		position = cur_pos - newDistance;

		// If touching ground
		if (position.y > 10.5f) {
			Insky = true;
			
			// inits explosion
			explosion.start(position);

			cout << "touched";
			//t0 = Time::now();	// reset first time
			
			position.y = 100.5f;	// put to default height
		}
	}

};