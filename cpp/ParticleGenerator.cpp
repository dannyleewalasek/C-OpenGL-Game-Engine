#include "../headers/ParticleGenerator.h"

ParticleGenerator::ParticleGenerator()
{

}

void ParticleGenerator::init()
{
	particleTexture.LoadTexture("Textures/meteor.png");
	for (int i = 0; i < 1000; i++)
	{
		struct particle part;
		part.posX = i*3;
		part.posY = i*3;
		part.Alive = false;
		particles[i] = part;
	}
}


ParticleGenerator::~ParticleGenerator()
{
}

//this is maybe redundant??
int ParticleGenerator::FindNextParticle()
{
	for (int i = 0; i < 1000; i++)
	{
		if (particles[i].Alive == false)
		{
			particles[i].Alive = true;
			return i;
		}
		else
			continue;
	}
}

void ParticleGenerator::RenderParticles()
{
	for (int i = 0; i < 1000; i++)
	{
		if (particles[i].Alive == true)
			SpriteRenderer::getInstance()->DrawMessage(&particleTexture, glm::vec2(particles[i].posX, particles[i].posY), glm::vec2(100, 100), 0, glm::vec2(0));
	}
}