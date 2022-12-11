#include <string>
#include <iostream>

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"

#include "Shader.h"

using namespace std;

float vertices[] = {
	-0.5f, -0.5f, 0.f, 0.5f, 0.f, 0.f,
	0.f, 0.5f, 0.f, 0.f, 0.5f, 0.f,
	0.5f, -0.5f, 0.f, 0.f, 0.f, 0.5f
};

void resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main(void) {
	GLFWwindow* window;

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

	window = glfwCreateWindow(1280, 720, "Hello World!", NULL, NULL);

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

	glViewport(0, 0, 1280, 720);
	glfwSetFramebufferSizeCallback(window, resize_callback);

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader shader("./shaders/vertex.shader", "./shaders/fragment.shader");

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
