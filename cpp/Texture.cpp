#include "../headers/Texture.h"

/**
 * Constructor sets inital values to 0.
 *
 */
Texture::Texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLoc = "";
}

/**
 * Load an image in from file and crate a Texture object using it.
 *
 * @param fileLocation const char pointer to the file system location of the PNG to be used as a texture.
 */
void Texture::LoadTexture(const char* fileLocation)
{
	fileLoc = fileLocation;

	unsigned char *texData = stbi_load(fileLoc, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		//error checking
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}

/**
 * Bind this texture on the PGU ready to draw.
 *
 */
void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

/**
 * Clears the texture data from the GPU/
 *
 */
void Texture::ClearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLoc = "";
}

/**
 * Destructor for the Texture removes texture data from the GPU before destorying Texture object.
 *
 */
Texture::~Texture()
{
	ClearTexture();
}
