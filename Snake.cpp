#include "Snake.h"
#include <iostream>

#define BUTTON_DPAD_UP 13
#define BUTTON_DPAD_DOWN 15
#define BUTTON_DPAD_LEFT 12
#define BUTTON_DPAD_RIGHT 14
#define BUTTON_MINUS 11
#define KEY_LSTICK_UP 17
#define KEY_LSTICK_DOWN 19
#define KEY_LSTICK_LEFT 16
#define KEY_LSTICK_RIGHT 18

// Overloaded constructor
Snake::Snake(SDL_Renderer *renderer) :
	snakeSegments(std::vector<Sprite>(3, Sprite(renderer, "romfs:/assets/snake_segment.png", 40, 40))),
	currentDirection(Direction::right),
	stopped(true),
	hasChangedDirection(false) 
{
	snakeSegments[0] = Sprite(renderer, "romfs:/assets/snake_head.png", 40, 40);

	this->resetPosition();
}

// Destructor
Snake::~Snake() {
	for (long unsigned int i = 0; i < this->snakeSegments.size(); ++i) {
		SDL_DestroyTexture(this->snakeSegments[i].getTexture());
	}
}

// Draws each segment of the snake
void Snake::draw() {
	for (Sprite segment : this->snakeSegments) {
		segment.draw();
	}
}

// Updates the snake's position and checks for collisions
void Snake::update() {

	// Check if next move will cause snake to collide with wall
	Sprite head = this->snakeSegments[0];
	if ((this->currentDirection == Direction::up && head.getY() == 0) ||
		(this->currentDirection == Direction::down && head.getY() == (720 - 40)) ||
		(this->currentDirection == Direction::left && head.getX() == 0) ||
		(this->currentDirection == Direction::right && head.getX() == (1280 - 40))) {
		this->stopped = true;
		this->resetPosition();
	}
	
	// Set new position
	if (!this->stopped) {
		for (long unsigned int i = this->snakeSegments.size() - 1; i >= 1; --i) {
			snakeSegments[i].setX(snakeSegments[i - 1].getX());
			snakeSegments[i].setY(snakeSegments[i - 1].getY());
		}
		if (this->currentDirection == Direction::up) {
			snakeSegments[0].changeYBy(-40);
		}
		else if (this->currentDirection == Direction::down) {
			snakeSegments[0].changeYBy(40);
		}
		else if (this->currentDirection == Direction::left) {
			snakeSegments[0].changeXBy(-40);
		}
		else if (this->currentDirection == Direction::right) {
			snakeSegments[0].changeXBy(40);
		}
	}

	// Check if snake has hit itself
	for (long unsigned int i = 1; i < this->snakeSegments.size(); ++i) {
		if (this->snakeSegments[0].getX() == this->snakeSegments[i].getX() &&
			this->snakeSegments[0].getY() == this->snakeSegments[i].getY()) {
			this->stopped = true;
			this->resetPosition();
		}
	}

}

// Checks the input queue and responds to the appropriate events
void Snake::checkInput(std::vector<SDL_Event> &events, unsigned short updateCounter) {
	if (!this->hasChangedDirection) {
		Direction previous = this->currentDirection;
		for (long unsigned int i = 0; i < events.size(); ++i) {
			if (events[i].type == SDL_JOYBUTTONDOWN) {
				switch (events[i].jbutton.button) {
					case BUTTON_DPAD_UP:
					case KEY_LSTICK_UP:
						if (this->currentDirection != Direction::down && !this->stopped) {
							this->currentDirection = Direction::up;
							this->snakeSegments[0].setAngle(270);
						}
						break;

					case BUTTON_DPAD_DOWN:
					case KEY_LSTICK_DOWN:
						if (this->currentDirection != Direction::up && !this->stopped) {
							this->currentDirection = Direction::down;
							this->snakeSegments[0].setAngle(90);
						}
						break;

					case BUTTON_DPAD_LEFT:
					case KEY_LSTICK_LEFT:
						if (this->currentDirection != Direction::right && !this->stopped) {
							this->currentDirection = Direction::left;
							this->snakeSegments[0].setAngle(180);
						}
						break;

					case BUTTON_DPAD_RIGHT:
					case KEY_LSTICK_RIGHT:
						if (this->currentDirection != Direction::left && !this->stopped) {
							this->currentDirection = Direction::right;
							this->snakeSegments[0].setAngle(0);
						}
						break;

					case BUTTON_MINUS:	// Pause/unpause game on enter press
						this->stopped = !this->stopped;
						break;

					default:
						break;
				}
			}
		}

		// Only change direction once per movement of the snake
		if (this->currentDirection != previous) {
			this->hasChangedDirection = true;
		}
	}

	if (updateCounter == 20) {
		this->hasChangedDirection = false;
	}
}

// Checks if the snake is in the same location as the food
bool Snake::ateFood(Food &food) {
	if (this->snakeSegments[0].getX() == food.getX() &&
		this->snakeSegments[0].getY() == food.getY()) {
		return true;
	}
	return false;
}

// Appends a new segment onto the snake
void Snake::increaseSize(SDL_Renderer *renderer) {
	Sprite newSegment = Sprite(renderer, "romfs:/assets/snake_segment.png", 40, 40);
	Sprite tail = this->snakeSegments[this->snakeSegments.size() - 1];
	newSegment.setX(tail.getX());
	newSegment.setY(tail.getY());
	this->snakeSegments.push_back(newSegment);
}

// Checks each segment for a collision
bool Snake::isCollidingWith(Sprite &sprite) {
	for (long unsigned int i = 0; i < this->snakeSegments.size(); ++i) {
		if (this->snakeSegments[i].isCollidingWith(sprite)) {
			return true;
		}
	}
	return false;
}

// Set segment coordinates to their default position
void Snake::resetPosition() {
	while (this->snakeSegments.size() > 3) {
		this->snakeSegments.pop_back();
	}
	for (long unsigned int i = 0; i < this->snakeSegments.size(); ++i) {
		this->snakeSegments[i].setX(200 - (i * 40));
		this->snakeSegments[i].setY(600);
	}
	this->currentDirection = Direction::right;
	this->snakeSegments[0].setAngle(0);
}