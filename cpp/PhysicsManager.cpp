#include "../headers/PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
}

void PhysicsManager::HandlePhysics(std::vector<PhysicsObject*> objects) {
	for (auto object : objects)
	{
		if (object->getAcceleration() != glm::vec2(0))
		{
			glm::vec2 position = object->GetPosition();
			position.x += ((object->getVelocity().x * object->getAcceleration().x)/10) * globals::deltaTime;
			position.y += ((object->getVelocity().y * object->getAcceleration().y)/10) * globals::deltaTime;

			object->setAccelerationX(object->getAcceleration().x * 0.9999);
			object->setAccelerationY(object->getAcceleration().y * 0.9999);
			object->SetPosition(position);
		}
	}
}


PhysicsManager::~PhysicsManager()
{
}
