#pragma once
class globals
{
public:
	static float height;//SHOULD BE CONST?
	static float width;//
	static float mousePosX;
	static float mousePosY;
	static float deltaTime;
	static float lastTime;
	static float currentTime;
	globals();
	~globals();
	void SetMousePosX(float mousePosX);
	void SetMousePosY(float mousePosY);
	void SetDeltaTime(float currentTime);
	void SetlastTime(float lastTime);
};

