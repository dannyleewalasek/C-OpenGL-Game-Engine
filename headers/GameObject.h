#pragma once
#include <iostream>
#include "SpriteRenderer.h"
#include "gameState.h"

class GameObject
{
private:
	Texture* texture;
	glm::vec2 size, position, rotationOffset;
	float rotation;
public:
	float creationTime;
	gameState type;
	void SetRotation(float rotation);
	void SetSize(glm::vec3 Size);
	void SetRotationOffset(glm::vec3 rotationOffset);
	Texture* GetTexture();
	void SetPosition(glm::vec2 position);
	void init(const char * filePath, glm::vec3 size, glm::vec3 position, char iD);
	void init(Texture * texture, glm::vec3 size, glm::vec3 position, char iD);
	void draw();
	float GetRotation();
	glm::vec2 GetSize();
	glm::vec2 GetPosition();
	GameObject();
	~GameObject();
	int objectID;

};

