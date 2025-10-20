#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <stdlib.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

// IMGUI for UI!!!


const float DEF_YAW = -90.0f;
const float DEF_PITCH = 0.0f;
const float DEF_SPEED = 2.5f;
const float DEF_FOV = 45.0f;
const float DEF_SENS = 0.1f;


enum Camera_Movement {
	FORWARD,
	BACKWARDS,
	LEFT,
	RIGHT,
	NONE
};


class Camera {

	public:
		void updateTestUI();
		
		// -- variables --
		// vectors
		glm::vec3 camPosition;
		glm::vec3 camFront;
		glm::vec3 camUp;
		glm::vec3 worldUp;
		glm::vec3 right;
		// movement
		float speed;
		float sensitivity;
		float fov;
		// euler angles
		float yaw;
		float pitch;

		// constructors
		Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float yaw, float pitch);
		Camera(float xpos, float ypos, float zpos, float xfront, float yfront, float zfront, float xup, float yup, float zup, float yaw, float pitch);

		// getters/setters
		glm::mat4 getView();

		// keyboard input
		void keyInput(Camera_Movement dir[], float deltaTime);

		// Mouse Input
		void mouseMovement(float xpos, float ypos);


	private:
		void updateCamVectors();

};

Camera::Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = DEF_YAW, float pitch = DEF_PITCH) : sensitivity(DEF_SENS), fov(DEF_FOV) {
	camPosition = pos;
	camFront = front;
	worldUp = up;
	camUp = worldUp;
	this->yaw = yaw;
	this->pitch = pitch;
	this->speed = DEF_SPEED;
	updateCamVectors();
}

Camera::Camera(float xpos = 0.0f, float ypos = 0.0f, float zpos = 0.0f, float xfront = 0.0f, float yfront = 0.0f, float zfront = -1.0f, float xup = 0.0f, float yup = 1.0f, float zup = 0.0f, float yaw = DEF_YAW, float pitch = DEF_PITCH) : sensitivity(DEF_SENS), fov(DEF_FOV) {
	camPosition = glm::vec3(xpos, ypos, zpos);
	camFront = glm::vec3(xfront, yfront, zfront);
	worldUp = glm::vec3(xup, yup, zup);
	camUp = worldUp;
	this->yaw = yaw;
	this->pitch = pitch;
	this->speed = DEF_SPEED;
	updateCamVectors();
}

// getters/setters

glm::mat4 Camera::getView() {
	return glm::lookAt(camPosition, camPosition + camFront, camUp);
}


void Camera::keyInput(Camera_Movement dir[], float deltaTime) {
	// dir[] = {FWD, BKWD, LEFT, RIGHT}!

	float camSpeed = static_cast<float>(speed * deltaTime); // maintain const speed

	if (dir[0] == FORWARD) {
		camPosition += camSpeed * camFront;
	}
	if (dir[1] == BACKWARDS) {
		camPosition -= camSpeed * camFront;
	}
	if (dir[2] == LEFT) {
		camPosition -= glm::normalize(glm::cross(camUp, right)) * camSpeed;
	}
	if (dir[3] == RIGHT) {
		camPosition += glm::normalize(glm::cross(camUp, right)) * camSpeed;
	}

}

void Camera::mouseMovement(float xoffset, float yoffset) {

	xoffset *= sensitivity;
	yoffset *= -sensitivity; // -sens allows for mouse up = look up and mouse down = look down

	yaw += xoffset;
	pitch += yoffset;

	// 90 degrees = lookAt flip!
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	updateCamVectors();
}

void Camera::updateCamVectors() {
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(direction);

	right = glm::normalize(glm::cross(camFront, worldUp));
	camUp = glm::normalize(glm::cross(right, camFront));
}

/*
void Camera::updateTestUI() {
	ImGuiIO& io = ImGui::GetIO();

	ImGui::Begin("Player Stats");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Velocity");
	ImGui::Text("X: %d", velocity.x);
	ImGui::SameLine();
	ImGui::Text("Y: %d", velocity.y);
	ImGui::SameLine();
	ImGui::Text("Z: %d", velocity.z);
	/*
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);
	*/
/*
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();
}
*/

#endif CAMERA_H
