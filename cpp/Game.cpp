
#include "../headers/Game.h"
#include <cstdlib>



int score = 0;
ParticleGenerator particleGenerator;
float lastShotTime = 0;
float fireRate = 0.1;

Game::Game()
	: currentState(MAIN_MENU)
{
}

/**
 * Initialize the Game.
 *
 * @param window A pointer to a GLFW Window object.
 */
void Game::init(GLFWwindow * window)
{
	// Set local variables
	this->window = window;
	resourceManager.LoadResourcesFromFile("example.txt");
	particleGenerator.init();
}

/**
 * Update loop for the game used to update the main game logic.
 *
 */
void Game::Update() { // Update loop user for per frame game update calculations
	glm::vec2 direction = glm::vec2(0, 0);

	if (Keys[GLFW_KEY_LEFT])
		direction.x = -1.0f;
	if (Keys[GLFW_KEY_RIGHT])
		direction.x = 1.0f;
	if (Keys[GLFW_KEY_UP])
		direction.y = -1.0f;
	if (Keys[GLFW_KEY_DOWN])
		direction.y = 1.0f;
	if (Keys[GLFW_KEY_SPACE])
		direction *= 2;
	if (direction != glm::vec2(0))
	{
		resourceManager.FindObject("cue")->SetPosition(glm::vec2(resourceManager.FindObject("cue")->GetPosition().x + direction.x, resourceManager.FindObject("cue")->GetPosition().y + direction.y));
	}

	if (Keys[GLFW_KEY_S] && globals::currentTime > lastShotTime + fireRate) {
		resourceManager.AddObject("Textures/bullet.png", 2, 2, resourceManager.FindObject("cue")->GetPosition().x, resourceManager.FindObject("cue")->GetPosition().y, IN_GAME, "bullet", MAIN_MENU);
	//	Keys[GLFW_KEY_S] = 0;
		resourceManager.FindObjectById(resourceManager.getID()-1)->setAccelerationX(100.0f);
		resourceManager.FindObjectById(resourceManager.getID()-1)->setAccelerationY(100.0f);
		resourceManager.FindObjectById(resourceManager.getID()-1)->setVelocityX(10.0f);
		resourceManager.FindObjectById(resourceManager.getID()-1)->setVelocityY(10.0f);
		lastShotTime = globals::currentTime;
	}
	
	/*
	std::vector<UIResource*> bullets = resourceManager.findObjectsWithName("bullet", 100);
	std::vector<UIResource*> meteors = resourceManager.findObjectsWithName("meteor", 100);
	for (int i = 0; i < bullets.size(); i++)
	{
		//bullets[i]->SetPosition(glm::vec3(bullets[i]->GetPosition().x, bullets[i]->GetPosition().y - 2.0f, -1.0f));
		if (globals::currentTime - bullets[i]->creationTime > 10)
			resourceManager.DeleteObject(bullets[i]->objectID);
			for (int j = 0; j < meteors.size(); j++)
			{
				std::vector<UIResource*> meteors = resourceManager.findObjectsWithName("meteor", 100);
				if (meteors.size() > 0)
				{
					if (DistanceBetween(bullets[i]->GetPosition(), meteors[j]->GetPosition()) < meteors[j]->GetSize().x)
					{
						score++;
						resourceManager.DeleteObject(meteors[j]->objectID);
						resourceManager.DeleteObject(bullets[i]->objectID);
						break;
					}
				}
			}

	}
	*/
	resourceManager.HandlePhysics();

	glm::vec2 aimDirection = glm::vec2(globals::width / 2 - globals::mousePosX, globals::height / 2 - globals::mousePosY);

	float distanceX = ((globals::width / 2) - globals::mousePosX) * ((globals::width / 2) - globals::mousePosX);
	float distanceY = ((globals::height / 2) - globals::mousePosY) * ((globals::height / 2) - globals::mousePosY);
	float distance = distanceX + distanceY;
	distance = sqrt(distance);

	aimDirection.x /= distance * -1;
	aimDirection.y /= distance * -1;
	resourceManager.LookAt("cue", aimDirection);

	if (Keys[GLFW_KEY_SPACE])
		resourceManager.FindObject("cue")->SetPosition(glm::vec2(resourceManager.FindObject("cue")->GetPosition().x + aimDirection.x, resourceManager.FindObject("cue")->GetPosition().y + aimDirection.y));
	SpriteRenderer::getInstance()->moveCamera(resourceManager.FindObject("cue")->GetPosition());

}

/**
 * Render loop for the game used to render all object to screen in the correct order.
 *
 */
void Game::Render() {
	
	if (currentState == MAIN_MENU) {
			resourceManager.DrawObjectsWithID(IN_GAME);
		}
	if (Keys[GLFW_KEY_F])
	{
		particleGenerator.FindNextParticle();
	}
	//	particleGenerator.RenderParticles();
		SpriteRenderer::getInstance()->Render();
}

/*
All following functions are used within the previous 3 initialize, update and rendering loops.
All functionality can be traced through the previous 3.
*/

/**
 * Resets all game data and starts a new game.
 *
 */
void Game::NewGame() {
}

/**
 * Change the current game state. Used to handle correct trainsitions between game states.
 *
 *@param newState the gamestate to be changed to.
 */
void Game::updateGameState(gameState newState) {
	if (newState == IN_GAME) {
		if (currentState == MAIN_MENU) {
			ResetGame();
		}
	}
	currentState = newState;
}



/**
 * Reset all game scores and colour assignments.
 *
 */
void Game::ResetGame() {

}


// Destructor
Game::~Game() {}


/**
 * Calculate the euclidean distance between two points.
 *
 *@return dist A float for the distance between the two points.
 */
float Game::DistanceBetween(glm::vec2 point1, glm::vec2 point2) {
	glm::vec2 PhysicsObjectToPhysicsObject = glm::vec2(point1.x - point2.x, point1.y - point2.y);
	float distX = sqrt((point1.x - point2.x) * (point1.x - point2.x));
	float distY = sqrt((point1.y - point2.y) * (point1.y - point2.y));
	float dist = distX + distY;
	return dist;
}