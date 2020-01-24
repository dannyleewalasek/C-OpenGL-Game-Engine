#pragma once
#include <vector>
#include "Texture.h"
#include "SpriteRenderer.h"
#include "../libraries/GLM/glm/glm.hpp"

class ParticleGenerator
{
private:
	struct particle {
	public:
		int posX;
		int posY;
		bool Alive;
	};
	particle particles[1000];
	Texture particleTexture;
public:
	ParticleGenerator();
	void init();
	~ParticleGenerator();
	int FindNextParticle();
	void RenderParticles();
};

