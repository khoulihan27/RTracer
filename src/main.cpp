#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <iostream>

#include "imgui.c"
#include "stb.c"

#include "../includes/shader.h"
#include "../includes/camera.h"


// abstract set-up and the global funcs into another file or class/struct later
	// i.e. screen class or something

bool firstMove = false;
float lastX = 0.0f;
float lastY = 0.0f;
float screenW = 800.0f;
float screenH = 600.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	screenW = width;
	screenH = height;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	// so it doesn't go wonky when first opening screen
	if (firstMove) {
		lastX = xpos;
		lastY = ypos;
		firstMove = false;
	}

	float xoffset = static_cast<float>(xpos) - lastX;
	float yoffset = static_cast<float>(ypos) - lastY;
	lastX = xpos;
	lastY = ypos;

	//player.mouseMovement(xoffset, yoffset);
}





int main() {

	// init stuff --> move to application/program class/struct to abstract
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Initializing Window Object
	GLFWwindow* window = glfwCreateWindow(screenW, screenH, "RT", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window..." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Woah nelly! Failed to initalize GLAD!" << std::endl;
		return -1;
	}


	glViewport(0, 0, 800, 600);

	// set global settings
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);



}