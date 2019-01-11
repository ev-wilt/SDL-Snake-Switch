#pragma once
#include "Sprite.h"
class Food :
	public Sprite
{
public:
	Food(SDL_Renderer *renderer, int width, int height);
	~Food();
	void resetPosition();
};

