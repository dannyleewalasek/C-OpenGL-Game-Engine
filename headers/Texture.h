#pragma once

#include "../libraries/GLEW/include/GL/glew.h"
#include <iostream>
#include "stb_image.h"
class Texture
{
public:
	Texture();
	~Texture();
	void LoadTexture(const char* fileLocation), UseTexture(), ClearTexture();
	GLint width, height, bitDepth;
private:
	GLuint textureID;
	const char* fileLoc;
};
