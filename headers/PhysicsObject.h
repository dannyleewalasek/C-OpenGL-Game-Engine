#pragma once
#include "GameObject.h"
#include "../libraries/GLM/glm/glm.hpp"
class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	~PhysicsObject();
	glm::vec2 getAcceleration();
	glm::vec2 getVelocity();
	void setAccelerationX(float acceleration), setAccelerationY(float acceleration);
	void setVelocityX(float velocity), setVelocityY(float velocity);
	float getMass();
private:
	glm::vec2 velocity;
	glm::vec2 acceleration;
	float mass = 0.8f;
};
