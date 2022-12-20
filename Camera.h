#pragma once

#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera {
public:
	Camera();

	void update(GLFWwindow * const window, float delta);
	
	void setPosition(glm::vec3 pos);
	void setOrientation(float yaw, float pitch);
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);

	glm::vec3 getPosition() const;
	glm::mat4 viewMatrix() const;
private:
	glm::vec3 up, position, front;
	float yaw, pitch;
	float speed;
	bool firstUpdate;
	
	struct {
		float lastX, lastY, sensitivity;
	} mouse;
};