#ifndef VISUAL_H
#define VISUAL_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shader.hpp"
#include "texture.hpp"

using namespace std;

class visual{
	private:
		GLFWwindow* window;
		double x = 0, y = 0, z = 0;

	public:
		void update_rotation(double x_, double y_, double z_);
		void start();
};

#endif