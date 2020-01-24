#pragma once
#include "Texture.h"
#include "shader.h"
#include <vector>

class SpriteRenderer
{
private:
	struct drawCall {
	Texture* sprite;
	glm::vec2 position;
	glm::vec2 size;
	float rotation;
	glm::vec2 rotationOffset;
};
	GLuint VAO, VBO, IBO;
	GLuint uniformModel, uniformProjection;
	Shader spriteShader;
	static SpriteRenderer* instance;
	SpriteRenderer();
	glm::vec2 cameraPosition;
	std::vector<drawCall> messageQueue;
public:
	void Render(Texture * sprite, glm::vec2 position, glm::vec2 size, float rotation, glm::vec2 rotationOffset);
	void Render();
	void DrawMessage(Texture * sprite, glm::vec2 position, glm::vec2 size, float rotation, glm::vec2 rotationOffset);
	~SpriteRenderer();
	static SpriteRenderer* getInstance();
	void moveCamera(glm::vec2 position);
};
