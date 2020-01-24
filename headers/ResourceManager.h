#pragma once
#include "SpriteRenderer.h"
#include "UIResource.h"
#include "PhysicsObject.h"
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include "../headers/PhysicsManager.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	void HandlePhysics();
	gameState Click(gameState gameState);
	void LoadResourcesFromFile(const char* fileLocation);
	void removeSpaces(char * s);
	void DrawObjectsWithName(std::string objectName, int max);
	std::vector<PhysicsObject*> findObjectsWithName(std::string objectName, int max);
	void DrawObjectsWithID(gameState ID);
	void RotateObject(std::string objectName, glm::vec3 rotation);
	void DrawObject(std::string objectName);
	void SetObjectPosition(std::string objectName, glm::vec3 position);
	void DeleteObject(int objectID);
	void DeleteObject(std::string objectName);
	void AddObject(const char * image, float sizeX, float sizeY, float posX, float posY, gameState state, std::string ID, gameState onClick);
	PhysicsObject* FindObject(std::string objectName);
	PhysicsObject* FindObjectById(int objectID);
	void LookAt(std::string origin, glm::vec2 lookAt);
	int getID();
	void LookAt(std::string origin, std::string endPoint);
private:
	PhysicsManager physicsManager;
	std::multimap<std::string, UIResource*> UIresources;
	std::multimap<std::string, PhysicsObject*> PhysicsObjects;
	std::multimap<std::string, Texture*> textures;

	bool IsUIResourceSelected(glm::vec2 position, glm::vec2 size);
};

