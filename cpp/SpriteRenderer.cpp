#include "../headers/SpriteRenderer.h"

SpriteRenderer* SpriteRenderer::instance = 0;

/**
 * Get the instance of the renderer. If the renderer is yet to be used the object is initialized.
 *
 * @return instance a pointer to the SpriteRenderer instance.
 */
SpriteRenderer* SpriteRenderer::getInstance()
{
	if (instance == 0)
	{
		instance = new SpriteRenderer();
	}

	return instance;
}

void SpriteRenderer::moveCamera(glm::vec2 position) {
	//remove arbitrary numbers
	cameraPosition.x = position.x - globals::width/2;
	cameraPosition.y = position.y - globals::height/2;
}

/**
 * Constructor fot the spreiteRenderer used to initialize a new sprite shader on the GPU.
 *
 */

int totalsprites;
GLfloat vertices[1000];
GLuint indices[300];

void imageSplitter(int sprites) {
	totalsprites = sprites;
	for (int i = 0; i < sprites; i++)
	{
		std::cout << (float)(1.00 / sprites) * i;
		//BOTTOM LEFT
		vertices[(i * 20)] = -1 + ((1.00 / sprites)*i * 2);
		vertices[(i * 20) + 1] = -1 + ((1.00 / sprites)*i * 2);
			vertices[(i * 20) + 2] = 0.0f; 
			vertices[(i * 20) + 3] = ((1 / sprites) * i) ;
			vertices[(i * 20) + 4] = ((1 / sprites) * i) ;
		//BOTTOM RIGHT
			vertices[(i * 20) + 5] = -1 + ((1.00 / sprites)*i * 2);
			vertices[(i * 20) + 6] = -0.6 + ((1.00 / sprites)*i * 2);
			vertices[(i * 20) + 7] = 0.0f;
			vertices[(i * 20) + 8] = ((1 / sprites) * i) + 1;	
			vertices[(i * 20) + 9] = ((1 / sprites) * i) ;
		//TOP RIGHT
			vertices[(i * 20) + 10] = -1 + ((1.00 / sprites)*i * 2);
			vertices[(i * 20) + 11] = -0.6 + ((1.00 / sprites)*i * 2);
			vertices[(i * 20) + 12] = 0.0f;
			vertices[(i * 20) + 13] = ((1 / sprites) * i) + 1;
			vertices[(i * 20) + 14] = ((1 / sprites) * i*5) + 1;
		//TOP LEFT
			vertices[(i * 20) + 15] = -0.6 + ((1.00 / sprites)*i * 2);
			vertices[(i * 20) + 16] = -0.6 + ((1.00 / sprites)*i * 2);
			vertices[(i * 20) + 17] = 0.0f;
			vertices[(i * 20) + 18] = ((1 / sprites) * i) ;
			vertices[(i * 20) + 19] = ((1 / sprites) * i) + 1;

			indices[i * 6] = (i * 3);
			indices[i*6  + 1] = (i * 3) + 3;
			indices[i*6 + 2] = (i * 3) + 1;
			indices[i*6 + 3] = (i * 3) + 1;
			indices[i*6 + 4] = (i * 3) + 2;
			indices[i*6 + 5] = (i * 3) + 3;

	}
}
SpriteRenderer::SpriteRenderer()
{
	spriteShader.initialize("Shaders/Shader.vert", "Shaders/Shader.frag");
	cameraPosition = glm::vec2(0.0f, 0.0f);
	spriteShader.SetMatrix(glm::ortho(0.0f, globals::width,globals::height, 0.0f, 0.1f, 100.0f), "projection");

	imageSplitter(10);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

/**
 * Render a sprite object to screen.
 *
 * @param sprite A pointer to the sprites Texture object.
 * @param position A 3 value vector for the world position of the sprite.
 * @param size A 3 value vector for the world size of the sprite.
 * @param rotation the rotation in radians of the sprite.
 * @param rotationOffset this is used to alter the pivot point of the object used in rotations.
 */
void SpriteRenderer::Render()
{
	Texture* previousTexture = nullptr;
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	// Model used for manipulation of positioning of object on screen
	glm::mat4 model = glm::mat4(1.0f);
	//while (!messageQueue.empty())
	for(int i = 0; i < 2; i++)
	{
		drawCall currentSprite = messageQueue.front();
		//messageQueue.erase(messageQueue.begin());

		//model = glm::translate(model, glm::vec3(currentSprite.position.x - cameraPosition.x + currentSprite.rotationOffset.y, +currentSprite.position.y - cameraPosition.y, -1.0));

		//model = glm::rotate(model, currentSprite.rotation, glm::vec3(0.0f, 0.0f, 1.0f));

		//model = glm::translate(model, glm::vec3(currentSprite.rotationOffset, -1.0));

		//model = glm::scale(model, glm::vec3(currentSprite.size.x, currentSprite.size.y, 1));

		//spriteShader.SetMatrix(model, "model");

	//	if (currentSprite.sprite != previousTexture)
	//	{
			currentSprite.sprite->UseTexture();
			glUseProgram(spriteShader.shaderID);
		//}

		glDrawElements(GL_TRIANGLES, 6 * totalsprites, GL_UNSIGNED_INT, 0);

		//reset the model
		//model = glm::mat4(1.0f);

		previousTexture = currentSprite.sprite;
	}


}

void SpriteRenderer::DrawMessage(Texture * sprite, glm::vec2 position, glm::vec2 size, float rotation, glm::vec2 rotationOffset) {
	drawCall newMsg = { sprite,position,size,rotation,rotationOffset };
	messageQueue.push_back(newMsg);
}



SpriteRenderer::~SpriteRenderer()
{}
