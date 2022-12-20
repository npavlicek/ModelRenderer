#include "Camera.h"

Camera::Camera() {
	position = glm::vec3(0, 0, 5.f);
	up = glm::vec3(0, 1.f, 0);
	front = glm::vec3(0, 0, 0);
	pitch = 0;
	yaw = -90.f;
	speed = 0.01f;
	mouse.sensitivity = 20.f;
	firstUpdate = true;
}

void Camera::update(GLFWwindow * const window, float delta) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += delta * speed * glm::normalize(front);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= delta * speed * glm::normalize(front);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= delta * speed * glm::normalize(glm::cross(front, up));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += delta * speed * glm::normalize(glm::cross(front, up));

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (firstUpdate) {
		mouse.lastX = mouseX;
		mouse.lastY = mouseY;
		firstUpdate = false;
	}

	float xOffset = mouseX - mouse.lastX;
	float yOffset = mouse.lastY - mouseY;
	mouse.lastX = mouseX;
	mouse.lastY = mouseY;

	xOffset *= mouse.sensitivity;
	yOffset *= mouse.sensitivity;

	yaw += xOffset * delta;
	pitch += yOffset * delta;

	if (pitch > 89.f)
		pitch = 89.f;
	if (pitch < -89.f)
		pitch = -89.f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);
}

void Camera::setPosition(glm::vec3 pos) {
	position = pos;
}

void Camera::setOrientation(float y, float p) {
	yaw = y;
	pitch = p;

	if (pitch > 89.f)
		pitch = 89.f;
	if (pitch < -89.f)
		pitch = -89.f;
}

void Camera::setSpeed(float s) {
	speed = s;
}

void Camera::setSensitivity(float s) {
	mouse.sensitivity = s;
}

glm::mat4 Camera::viewMatrix() const {
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getPosition() const {
	return position;
}