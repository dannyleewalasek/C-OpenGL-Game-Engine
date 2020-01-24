#include "../headers/PhysicsObject.h"

PhysicsObject::PhysicsObject()
	: velocity(glm::vec2(0)), acceleration(glm::vec2(0))
{
}

/**
 * Get the current velocity of the PhysicsObject.
 *
 * @return velocity The 3 axis vector for the PhysicsObjects velocity.
 */
glm::vec2 PhysicsObject::getVelocity()
{
	return velocity;
}


/**
 * Get the current acceleration of the PhysicsObject.
 *
 * @return acceleration The 3 axis vector for the PhysicsObjects acceleration.
 */
glm::vec2 PhysicsObject::getAcceleration()
{
	return acceleration;
}

/**
 * Get the current acceleration of the PhysicsObject.
 *
 * @return acceleration The 3 axis vector for the PhysicsObjects acceleration.
 */
float PhysicsObject::getMass()
{
	return mass;
}

/**
 * Set the current acceleration of the PhysicsObject in the x-axis.
 *
 * @param acceleration The float value to set as the x-axis acceleration.
 */
void PhysicsObject::setAccelerationX(float acceleration)
{
	this->acceleration.x = acceleration;
}

/**
 * Set the current acceleration of the PhysicsObject in the y-axis.
 *
 * @param acceleration The float value to set as the y-axis acceleration.
 */
void PhysicsObject::setAccelerationY(float acceleration)
{
	this->acceleration.y = acceleration;
}

/**
 * Set the current velocity of the PhysicsObject in the x-axis.
 *
 * @param velocity The float value to set as the x-axis velocity.
 * @param velocity The float value to set as the x-axis velocity.
 */
void PhysicsObject::setVelocityX(float velocity)
{
	this->velocity.x = velocity;
}

/**
 * Set the current velocity of the PhysicsObject in the y-axis.
 *
 * @param velocity The float value to set as the y-axis velocity.
 */
void PhysicsObject::setVelocityY(float velocity)
{
	this->velocity.y = velocity;
}
