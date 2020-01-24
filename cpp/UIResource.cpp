#include "../headers/UIResource.h"

/**
 * Returns the state to which the game should enter if the resource is clicked.
 *
 * @return onClick the gamestate to which the game should switch to.
 */
gameState UIResource::GetOnClick()
{
	return onClick;
}

/**
 * Set the gameState to which the game should switch to if the button is clicked.
 *
 * @param onClick the gamestate to be set to.
 */
void UIResource::SetOnClick(gameState onClick)
{
	this->onClick = onClick;
}

UIResource::UIResource()
{
}


UIResource::~UIResource()
{
}
