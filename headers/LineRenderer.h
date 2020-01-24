#pragma once
#include "Shader.h"
#include "globals.h"

class LineRenderer
{
private:
	GLuint VAO, VBO, IBO;
	GLuint uniformModel, uniformProjection;
	Shader lineShader;
public:
	Shader* getShader();
	LineRenderer();
	~LineRenderer();
	void init();
	void Render(glm::vec3 startPoint, glm::vec3 endPoint);
	void SetFloat(float value1, float value2, const char* name);
};

