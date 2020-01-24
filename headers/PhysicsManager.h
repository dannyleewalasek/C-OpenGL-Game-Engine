#pragma once

#include "../libraries/GLM/glm/glm.hpp"
#include <vector>
#include "../headers/PhysicsObject.h"

class PhysicsManager
{
public:
	PhysicsManager();
	void HandlePhysics(std::vector<PhysicsObject*> objects);
	~PhysicsManager();
};

