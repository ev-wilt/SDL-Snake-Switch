#pragma once
#include <vector>
#include "Sprite.h"
#include "Food.h"

enum Direction { up, down, left, right };

class Snake
{
public:
	Snake(SDL_Renderer *renderer);
	~Snake();
	void draw();
	void update();
	void checkInput(std::vector<SDL_Event> &events, unsigned short updateCounter);
	bool ateFood(Food &food);
	void increaseSize(SDL_Renderer *renderer);
	bool isCollidingWith(Sprite &sprite);
	void resetPosition();

private:
	std::vector<Sprite> snakeSegments;
	Direction currentDirection;
	bool stopped;
	bool hasChangedDirection;
};

