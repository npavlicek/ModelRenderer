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
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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

unsigned int createTexture(const char * filepath) {
	unsigned int imageID;
	glGenTextures(1, &imageID);
	glBindTexture(GL_TEXTURE_2D, imageID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	GLenum type;
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
	switch (nrChannels) {
	case 4:
		type = GL_RGBA;
		break;
	default:
		type = GL_RGB;
	}
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "Error loading texture! " << filepath << std::endl;
	}

	stbi_image_free(data);

	return imageID;
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

	glClearColor(0, 0, 0, 1.f);
	glEnable(GL_DEPTH_TEST);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.f), (float)WIDTH / HEIGHT, 0.1f, 100.f);

	glm::mat4 centerModel = glm::mat4(1.f);
	glm::mat4 lightModel = glm::mat4(1.f);

	Shader cubeShader("./shaders/cube.vs", "./shaders/cube.fs");
	Shader lightCubeShader("./shaders/lightCube.vs", "./shaders/lightCube.fs");
	Camera camera;

	unsigned int containerDiffuse = createTexture("./assets/container2.png");
	unsigned int containerSpecular = createTexture("./assets/container2_specular.png");

	glm::vec3 cubeColor(0.3f, 0, 0.5f);
	glm::vec3 lightColor(1.f);
	glm::vec3 lightCubePos(2.f, 0.f, 1.f);

	cubeShader.use();
	cubeShader.setMat4("projection", projection);

	cubeShader.setFloat("material.shininess", 64.f);

	cubeShader.setVec3("light.position", lightCubePos);
	cubeShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
	cubeShader.setVec3("light.diffuse", 1.f, 1.f, 1.f);
	cubeShader.setVec3("light.specular", 1.f, 1.f, 1.f);

	cubeShader.setInt("material.diffuse", 0);
	cubeShader.setInt("material.specular", 1);

	lightCubeShader.use();
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, containerDiffuse);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, containerSpecular);

	const float maxFPS = 144;
	const float maxPeriod = 1 / maxFPS;

	float lastTime = glfwGetTime();
	float frames = 0, updates = 0, lastUpdate = glfwGetTime();
	bool vsync = false;

	float angle = 0;

	while (!glfwWindowShouldClose(window)) {
		float time = glfwGetTime();
		float deltaTime = time - lastTime;

		// if statement to render at specified framerate
		if (vsync || (deltaTime >= maxPeriod)) {
			lastTime = time;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.update(window, deltaTime);

			lightCubePos.x = cos(angle) * 2;
			lightCubePos.z = sin(angle) * 2;

			// Render center cube
			cubeShader.use();

			cubeShader.setVec3("light.position", lightCubePos);

			cubeShader.setMat4("model", centerModel);
			cubeShader.setMat4("view", camera.viewMatrix());
			cubeShader.setVec3("viewPos", camera.getPosition());

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Render light cube
			lightCubeShader.use();
			lightModel = glm::translate(glm::mat4(1.f), lightCubePos);
			lightModel = glm::scale(lightModel, glm::vec3(0.2f));
			lightCubeShader.setMat4("model", lightModel);
			lightCubeShader.setMat4("view", camera.viewMatrix());

			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			angle += 1 * deltaTime;

			glfwSwapBuffers(window);

			frames++;
		}

		// Frame Counter every second
		float timeSinceUpdate = glfwGetTime() - lastUpdate;
		if (timeSinceUpdate >= 5) {
			float fps = frames / timeSinceUpdate;
			float ups = updates / timeSinceUpdate;
			std::cout << "Total frames: " << frames << ", total updates: " << updates << ", time passed: " << timeSinceUpdate << " seconds." << std::endl;
			std::cout << "FPS: " << fps << std::endl;
			std::cout << "UPS: " << ups << std::endl;
			std::cout << "Delta: " << deltaTime << std::endl;
			std::cout << "-------------------------------------------" << std::endl;
			updates = 0;
			frames = 0;
			lastUpdate = glfwGetTime();
		}

		updates++;

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
