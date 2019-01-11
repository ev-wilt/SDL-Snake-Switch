#include "Food.h"
#include <cstdlib>
#include <ctime>

// Overloaded constructor
Food::Food(SDL_Renderer *renderer, int width, int height):
	Sprite(renderer, "romfs:/assets/food.png", width, height)
{
	srand(time(NULL));
	this->resetPosition();
}

// Destructor
Food::~Food() {
	SDL_DestroyTexture(this->getTexture());
}

// Updates the food to a new random position
void Food::resetPosition() {
	this->setY((std::rand() / 40 * 40) % (720 - 40));
	this->setX((std::rand() / 40 * 40) % (1280 - 40));
}