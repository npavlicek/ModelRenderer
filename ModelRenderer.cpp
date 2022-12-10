#include "ModelRenderer.h"

#include <string>
#include <iostream>

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"

using namespace std;

int main(void)
{
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

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
