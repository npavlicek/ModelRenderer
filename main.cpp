#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"

#define WIDTH 1280
#define HEIGHT 720

using namespace std;

GLFWwindow* window;

// Cube vertices and normals
float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

void resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
	if (key == GLFW_KEY_H && action == GLFW_PRESS)
		glfwIconifyWindow(window);
}

int init() {
	if (!glfwInit()) {
		std::cerr << "Could not initialize GLFW!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int glfwMaj, glfwMin, glfwRev;
	glfwGetVersion(&glfwMaj, &glfwMin, &glfwRev);
	std::cout << "GLFW version " << glfwMaj << "." << glfwMin << "." << glfwRev << " initialized" << std::endl;

	window = glfwCreateWindow(WIDTH, HEIGHT, "Model Renderer", NULL, NULL);

	if (!window) {
		std::cerr << "Could not create the GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();

	if (GLEW_OK != err) {
		std::cerr << "Could not initialize GLEW!" << std::endl;
		return -1;
	}

	std::cout << "GLEW version " << glewGetString(GLEW_VERSION) << " initialized" << std::endl;

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSwapInterval(0);
	glfwSetFramebufferSizeCallback(window, resize_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return 0;
}

int main(void) {
	if (int err = init())
		return err;

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.f), (float)WIDTH / HEIGHT, 0.1f, 100.f);

	glm::mat4 model = glm::mat4(1.f);

	Shader cubeShader("./shaders/cube.vs", "./shaders/cube.fs");
	Shader lightCubeShader("./shaders/lightCube.vs", "./shaders/lightCube.fs");
	Camera camera;

	glm::vec3 cubeColor(0.3f, 0, 0.5f);
	glm::vec3 lightColor(1.f);
	glm::vec3 lightCubePos(2.f, 0.f, 1.f);

	cubeShader.use();
	cubeShader.setMat4("projection", projection);

	cubeShader.setVec3("material.ambient", 0.24725f, 0.1995f, 0.0745f);
	cubeShader.setVec3("material.diffuse", 0.75164f, 0.60648f, 0.22648f);
	cubeShader.setVec3("material.specular", 0.628281f, 0.555802f, 0.366065f);
	cubeShader.setFloat("material.shininess", 0.4f * 128.f);

	cubeShader.setVec3("light.position", lightCubePos);
	cubeShader.setVec3("light.ambient", 1.f, 1.f, 1.f);
	cubeShader.setVec3("light.diffuse", 1.f, 1.f, 1.f);
	cubeShader.setVec3("light.specular", 1.f, 1.f, 1.f);

	lightCubeShader.use();
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);

	const float maxFPS = 144;
	const float maxPeriod = 1 / maxFPS;

	float lastTime = glfwGetTime();
	float frames = 0, lastUpdate = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		float time = glfwGetTime();
		float deltaTime = time - lastTime;

		camera.update(window, deltaTime);

		// if statement to render at specified framerate
		if (deltaTime >= maxPeriod) {
			lastTime = time;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render center cube
			cubeShader.use();
			model = glm::mat4(1.f);
			cubeShader.setMat4("model", model);
			cubeShader.setMat4("view", camera.viewMatrix());
			cubeShader.setVec3("viewPos", camera.getPosition());

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Render light cube
			lightCubeShader.use();
			model = glm::translate(glm::mat4(1.f), lightCubePos);
			model = glm::scale(model, glm::vec3(0.2f));
			lightCubeShader.setMat4("model", model);
			lightCubeShader.setMat4("view", camera.viewMatrix());

			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glfwSwapBuffers(window);

			frames++;
		}

		// Frame Counter every second
		float timeSinceUpdate = glfwGetTime() - lastUpdate;
		if (timeSinceUpdate >= 1) {
			float fps = frames / timeSinceUpdate;
			std::cout << "Total frames: " << frames << ", time passed: " << timeSinceUpdate << " seconds." << std::endl;
			std::cout << "FPS: " << fps << std::endl;
			frames = 0;
			lastUpdate = glfwGetTime();
		}

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
