#pragma once
#include "shader.h"
class TextRenderer
{
private:
	Shader textShader;
public:
	void initText2D(const char * texturePath);
	void printText2D(const char * text, int x, int y, int size);
	void cleanupText2D();
	TextRenderer();
	~TextRenderer();
};

