#include "Shader.h"

Shader::Shader(const char * vertexShaderFilePath, const char * fragmentShaderFilePath) {
	const char* vertexSource = Shader::loadShaderSource(vertexShaderFilePath);
	const char* fragmentSource = Shader::loadShaderSource(fragmentShaderFilePath);

	unsigned int vertexShader, fragmentShader;

	int success;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "VERTEX SHADER COMPILE ERROR\n" << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "VERTEX SHADER COMPILE ERROR\n" << infoLog << std::endl;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "SHADER PROGRAM LINK ERROR\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(programID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

const char* Shader::loadShaderSource(const char* filePath) {
	std::ifstream file(filePath, std::ios::in | std::ios::ate);
	if (file.is_open()) {
		auto size = file.tellg();
		std::string str(size, '\0');
		file.seekg(0);
		file.read(&str[0], size);
		return str.c_str();
	}
	else {
		std::cout << "ERROR READING FILE: " << filePath << std::endl;
		return NULL;
	}
}