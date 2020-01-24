#pragma once
#include <iostream>
#include <vector>
#include "../libraries/GLEW/include/GL/glew.h"
#include "../libraries/GLFW/include/GLFW/glfw3.h"
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include "LineRenderer.h"
#include "ResourceManager.h"
#include "../libraries/tinyxml2/tinyxml2.h"
#include "ParticleGenerator.h"

class Game
{
private:
	gameState currentState;
	LineRenderer lineRenderer;
	ResourceManager resourceManager;
	void ResetGame();
	GLFWwindow* window;
	void updateGameState(gameState newState), SaveGame(), LoadGame(), NewGame();
	bool incorrectPhysicsObjectHit = false;
	bool pointScored = false;
	float DistanceBetween(glm::vec2 point1, glm::vec2 point2);
	glm::vec2 spin = glm::vec2(0);
public:
	glm::vec2 mousePosition;
	GLboolean Keys[1024];
	Game();
	~Game();
	void init(GLFWwindow* window), Render(), Update();
};

