#include "../headers/ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}


void ResourceManager::HandlePhysics()
{
	std::vector<PhysicsObject*> objects;
	for (std::map<std::string, PhysicsObject*>::iterator it = PhysicsObjects.begin(); it != PhysicsObjects.end(); ++it)
	{
		objects.push_back(it->second);
	}
	physicsManager.HandlePhysics(objects);
}

/**
 * Used to check if a clickable GameObject has been clicked on and returns the new gameState to which the game should transition to.
 *
 * @param gameState the current gameState of the game.
 * @return gameState the new gameState after clicking an object.
 */
gameState ResourceManager::Click(gameState gameState) {
	bool clickedFlag = false;
			for (std::map<std::string, UIResource*>::iterator it = UIresources.begin(); it != UIresources.end(); ++it)
			{
				if (IsUIResourceSelected(it->second->GetPosition(), it->second->GetSize()) && it->first != "background"
					&& it->second->type == gameState)
				{
					clickedFlag = true;
					return it->second->GetOnClick();
				}
			}
		if (clickedFlag == false)
			return gameState;
}


/**
 * Check if mouse is currently places on top of a clickable object.
 *
 * @param position The centre position of the gameObject to be checked.
 * @param size The 3 value size of the gameobject in pixels.
 * @return bool Return true if the mouse is on top of the object, false if not.
 */
bool ResourceManager::IsUIResourceSelected(glm::vec2 position,glm::vec2 size)
{
	return (globals::mousePosX > position.x - size.y && globals::mousePosX < position.x + size.y
		&& globals::mousePosY < position.y + size.x && globals::mousePosY > position.y - size.x);
}

int ResourceManager::getID()
{
	return PhysicsObjects.size();
}

/**
 * Add a new object to the resource manager
 *
 * @param image The file location for the .PNG image to be used as the sprite for the GameObject
 * @param sizeX The size the gameObject will be on screen, written in terms of % of screen space, for example:
 *				sizeX = 10; Would mean the gameObject takes up 10% of the screen accross the x-axis.
 * @param sizeY The size the gameObject will be on screen, written in terms of % of screen space, for example:
 *				sizeY = 10; Would mean the gameObject takes up 10% of the screen accross the y-axis. 
 * @param posX The position of the gameObject on screen, written in terms of % of screen space, for example:
 *				posX = 10; Would mean the gameObjects centre would be 10% accross the x-axis.
 * @param posY The position of the gameObject on screen, written in terms of % of screen space, for example:
 *				posY = 10; Would mean the gameObjects centre would be 10% accross the y-axis.
 * @param state The gameState in which the gameObject will be used.
 * @param ID The ID used to search for the gameObject.
 * @param onClick The gameState to which the game will transition to if the gameObject were clicked.
*/
void ResourceManager::AddObject(const char* image, float sizeX, float sizeY, float posX, float posY, gameState state, std::string ID, gameState onClick)
{

	PhysicsObject* UIresource = new PhysicsObject();
	if (textures.count((std::string)image) == 0)
	{
		Texture* texture = new  Texture();
		texture->LoadTexture(image);
		textures.insert(std::pair<std::string, Texture*>(ID, texture));
		UIresource->init(texture, glm::vec3((globals::height / 100) * sizeX, (globals::width / 100) * sizeY, 1.0), glm::vec3(posX, posY, -1.0), PhysicsObjects.size());
	}
	else
	{
		UIresource->init(textures.find((std::string)image)->second, glm::vec3((globals::height / 100) * sizeX, (globals::width / 100) * sizeY, 1.0), glm::vec3(posX, posY, -1.0), PhysicsObjects.size());

	}
	UIresource->type = state;
	PhysicsObjects.insert(std::pair<std::string, PhysicsObject*>(ID, UIresource));
}

/**
 * Used to find a resource using just the objects name
 *
 * @param objectName A string of the object to be founds name.
 * @return Object returns the found object or NULL if no objects are found.
 */
PhysicsObject* ResourceManager::FindObject(std::string objectName) {
	if (PhysicsObjects.count(objectName) > 0)
		return PhysicsObjects.find(objectName)->second;
	else
		return NULL;
}

PhysicsObject* ResourceManager::FindObjectById(int objectID) {
	for (std::multimap<std::string, PhysicsObject*>::iterator itr = PhysicsObjects.begin(); itr != PhysicsObjects.end(); ++itr)
	{
		if (itr->second->objectID == objectID)
		{
			return itr->second;
		}
	}
}

void ResourceManager::LookAt(std::string origin, glm::vec2 lookAt)
{
	glm::vec2 aimDirection;
	if (origin == "cue")
	{
		RotateObject(origin, glm::vec3(lookAt, 0));
	}

	else
	{
		aimDirection = glm::vec2(fabs(FindObject(origin)->GetPosition().x) - fabs(globals::mousePosX), fabs(FindObject(origin)->GetPosition().y) - fabs(globals::mousePosY));

		float distanceX = (globals::mousePosX - FindObject(origin)->GetPosition().x);
		float distanceY = (globals::mousePosY - FindObject(origin)->GetPosition().y);
		float distance = distanceX + distanceY;
		distance = sqrt(distance);

		aimDirection.x /= distance;
		aimDirection.y /= distance;

		RotateObject(origin, glm::vec3(aimDirection, 0));
	}
}



/**
 * Used to load resources in from file at run time.
 *
 * @param fileLocation the location of the file containing all object information.
 */
void ResourceManager::LoadResourcesFromFile(const char* fileLocation) 
{
	std::vector<std::string> resourcesList;
	std::ifstream ifs(fileLocation);
	std::string content;
	content.assign((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	std::stringstream ss(content);
	std::string to;

		while (std::getline(ss, to, '\n')) {
			resourcesList.push_back(to);
		}
		for (unsigned int i = 0; i < resourcesList.size(); i++)
		{
			std::stringstream ss(resourcesList[i]);
			std::string to;
			char *imageCopy;
			char *nameCopy;
			std::vector<char*> names;
			std::vector<char*> images;
			std::string image;
			float width;
			float height;
			float sizeX;
			float sizeY;
			gameState state;
			std::string name;
			gameState onClick;
			int objectID;

			int count = 0;
			while (std::getline(ss, to, ',')) {
				switch (count) {
				case 0: image = to;
					break;
				case 1:	width = std::stof(to);
					break;
				case 2: height = std::stof(to);
					break;
				case 3: sizeX = std::stof(to);
					break;
				case 4: sizeY = std::stof(to);
					break;
				case 5: state = (gameState)std::stoi(to);
					break;
				case 6:  name = to;
					break;
				case 7: onClick = (gameState)std::stoi(to);
				}
				count++;

			}
			imageCopy = new char[100];
			strcpy(imageCopy, image.c_str());
			removeSpaces(imageCopy);

			AddObject(imageCopy, width, height, sizeX, sizeY, state,name , onClick);
			delete [] imageCopy;
		}
}

void ResourceManager::removeSpaces(char* s)
{
	char* cpy = s; 
	char* temp = s;

	while (*cpy)
	{
		if (*cpy != ' ')
			*temp++ = *cpy;
		cpy++;
	}
	*temp = 0;
}
/**
 * Draw all objects with a certain name.
 *
 * @param objectName A string of the object to be founds name.
 * @param max An integer to determine the maximum amount of objects by a name to draw.
 */
void ResourceManager::DrawObjectsWithName(std::string objectName, int max) {
		int count = 0;
		for (std::multimap<std::string, PhysicsObject*>::iterator itr = PhysicsObjects.begin(); itr != PhysicsObjects.end(); ++itr)
		{
			if (count < max && itr->first == objectName)
			{
				itr->second->draw();
				count++;
			}
		}
}
std::vector<PhysicsObject*> ResourceManager::findObjectsWithName(std::string objectName, int max) {
	int count = 0;
	std::vector<PhysicsObject*> found;
	for (std::multimap<std::string, PhysicsObject*>::iterator itr = PhysicsObjects.begin(); itr != PhysicsObjects.end(); ++itr)
	{
		if (count < max && itr->first == objectName)
		{
			found.push_back(itr->second);
			count++;
		}
	}
	return found;
}

/**
 * Draw object with a specific gameState ID. Used to draw all objects in a specific scene for example "mainmenu".
 *
 * @param ID The gamestate to be rendered.
 */
void ResourceManager::DrawObjectsWithID(gameState ID) {
	for (std::multimap<std::string, PhysicsObject*>::iterator itr = PhysicsObjects.begin(); itr != PhysicsObjects.end(); ++itr)
	{
		if (itr->second->type == ID)
		{
			itr->second->draw();
		}
	}
}

/**
 * Rotate a specific object by a specified amount.
 *
 * @param objectName A string of the object to be founds name.
 * @param rotation The new rotation of the object.
 */
void ResourceManager::RotateObject(std::string objectName, glm::vec3 rotation)
{
	if (rotation.y > 0)
		FindObject(objectName)->SetRotation(3.14159 - (rotation.x * 1.5708));
	else
		FindObject(objectName)->SetRotation(0 + (rotation.x * 1.5708));
}

/**
 * Draw an object using its object name.
 *
 * @param objectName A string of the object to be founds name.
 */
void ResourceManager::DrawObject(std::string objectName)
{
	FindObject(objectName)->draw();
}

/**
 * Set a specific objects world position.
 *
 * @param objectName A string of the object to be founds name.
 * @param position the new position of the object.
 */
void ResourceManager::SetObjectPosition(std::string objectName, glm::vec3 position)
{
	FindObject(objectName)->SetPosition(position);
}

/**
 * Delete a specific object by name,
 *
 * @param objectName A string of the object to be deleteds name.
 */
void ResourceManager::DeleteObject(int objectID)
{
	//MUST BE A BETTER WAY BY REMOVING BY INDEX BUT MAYBE  NOT? THIS WORKS ANYWAY

	for (std::multimap<std::string, PhysicsObject*>::iterator itr = PhysicsObjects.begin(); itr != PhysicsObjects.end(); ++itr)
	{
		if (itr->second->objectID == objectID)
		{
			PhysicsObjects.erase(itr);
			break;
		}
	}
}