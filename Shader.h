#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "GL/glew.h"

class Shader {
public:
	unsigned int programID;

	Shader(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	/** Loads and returns file contents from the given filename. Does not abort on error.
	* @param[in] filename Name of file to read.
	* @returns The c string of the file contents upon successful read of file. Returns a NULL otherwise.
	*/
	const char* loadShaderSource(const char* filePath);
};