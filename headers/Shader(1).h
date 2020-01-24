#pragma once
#include "libraries/GLEW/include/GL/glew.h"
#include "libraries/GLM/glm/gtc/matrix_transform.hpp"
#include "libraries/GLM/glm/gtc/type_ptr.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "globals.h"
class Shader
{
private:
	void clearShader();
	GLuint uniform;
public:
	void initialize(const char*vertLocation, const char* fragLocation);
	void SetMatrix(glm::mat4 matrix, const char* uniformName);
	void Set2Float(GLfloat float1, GLfloat float2,const char* uniformName);
	GLuint shaderID;
	Shader();
	~Shader();
};

