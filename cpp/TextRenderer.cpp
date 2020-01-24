#include "../headers/TextRenderer.h"


TextRenderer::TextRenderer()
{
	textShader.initialize("Shaders/TextShader.vert", "Shaders/TextShader.frag");
}


TextRenderer::~TextRenderer()
{
}

void TextRenderer::initText2D(const char * texturePath)
{

}

void TextRenderer::printText2D(const char * text, int x, int y, int size)
{
}

void TextRenderer::cleanupText2D()
{
}