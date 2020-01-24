#include "../headers/GameObject.h"

GameObject::GameObject()
	:rotation(1.5708f), rotationOffset(glm::vec3(0))
{}

/**
 * All GameObjects must be initialized before they can be drawn.
 *
 * @param filePath The path to the tecture to be used to draw the GameObject
 * @param size 3 value vector for the size of the sprite on screen in pixels
 * @param ID The ID of the object, used to determine what screen the GameObject will be used in
 */
void GameObject::init(Texture* texture, glm::vec3 size , glm::vec3 position, char iD)
{
	this->size = size;
	this->position = position;
	this->objectID = iD;
	this->texture = texture;
	this->creationTime = globals::currentTime;
}

/**
 * Used to draw the GameObjects sprite to screen.
 *
 */
void GameObject::draw()
{
	SpriteRenderer::getInstance()->DrawMessage(texture, position, size, rotation, rotationOffset);
}

/**
 * Destructor ensures the texture is also removed from the GPU's memory on destruction of 
 * the GameObject.
 *
 */
GameObject::~GameObject()
{
}

/**
 * Get the current rotation of the GameObject
 *
 * @return rotation in radian
 *
 */
float GameObject::GetRotation()
{
	return rotation;
}

/**
 * Set the current rotation of the GameObject.
 *@param rotation Rotation in radian the GameObject is to be set to.
 *
 */
void GameObject::SetRotation(float rotation)
{
	this->rotation = rotation;
}

/**
 * Get the current position of the GameObject.
 *
 * @return position The position of the GameObject in pixel screen-space
 *
 */
glm::vec2 GameObject::GetPosition()
{
	return position;
}

/**
 * Set the current position of the GameObject.
 *@param position 3 value vector of the new position for the GameObject in pixel screen-space
 *
 */
void GameObject::SetPosition(glm::vec2 position)
{
	this->position = position;
}

/**
 * Get the size of the GameObject.
 *
 * @return 3 value vector of the size of the GameObject in pixel screen-space
 *
 */
glm::vec2 GameObject::GetSize()
{
	return size;
}

/**
 * Set the size of the GameObject.
 *
 *@param psize 3 value vector of the new size for the GameObject in pixel screen-space
 *
 */
void GameObject::SetSize(glm::vec3 Size)
{
	this->size = size;
}

/**
 * Set the rotation point for the GameObject, used to adjust the origin of rotation.
 *@param rotation 3 value vector of the new position used to rotate the GameObject around.
 *
 */
void GameObject::SetRotationOffset(glm::vec3 rotationOffset)
{
	this->rotationOffset = rotationOffset;
}
