#pragma once
#include "gameState.h"
#include "GameObject.h"
class UIResource : public GameObject
{
private:
	gameState onClick;
public:
	gameState GetOnClick();
	void SetOnClick(gameState onClick);
	UIResource();
	~UIResource();
};

