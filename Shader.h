#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Shader {
public:
	unsigned int programID;

	Shader(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 mat) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec3(const std::string& name, glm::vec3 vec) const;

private:
	/** Loads and returns file contents from the given filename. Does not abort on error.
	* @param[in] filename Name of file to read.
	* @returns Returns a CPP string with the file contents.
	*/
	std::string loadShaderSource(const char* filePath);
};