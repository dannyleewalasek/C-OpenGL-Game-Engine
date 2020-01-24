#include "../headers/globals.h"

globals::globals()
{
}

globals::~globals()
{
}

/**
 * Set the current mouse position in the X-axis.
 *@param mousePosX the float of the current mouse position in the X-axis.
 *
 */
void globals::SetMousePosX(float mousePosX)
{
	this->mousePosX = mousePosX;
}

/**
 * Set the current mouse position in the Y-axis.
 *@param mousePosX the float of the current mouse position in the Y-axis.
 *
 */
void globals::SetMousePosY(float mousePosY)
{
	this->mousePosY = mousePosY;
}

/**
 * Set the deltaTime of the game. This is the amount of time between frames.
 *@param currentTime the current time as a float.
 */
void globals::SetDeltaTime(float currentTime)
{
	this->currentTime = currentTime;
	deltaTime = currentTime - lastTime;
	SetlastTime(currentTime);
}

/**
 * Set the last time of the system. This is the time at which the last frame was entered. this is used to calculate the deltatime between frames.
 *@param lastTime the current time as a float.
 */
void globals::SetlastTime(float lastTime)
{
	this->lastTime = lastTime;
}

