#include "Sprite.h"
#include <iostream>

// Overloaded Constructor
Sprite::Sprite(SDL_Renderer *renderer, const char *filename, int width, int height) :
	renderer(renderer),
	imageTexture(IMG_LoadTexture(renderer, filename)),
	width(width),
	height(height),
	x(0),
	y(0),
	angle(0)
{
	if (imageTexture == NULL) {
		std::cerr << "Failed to load IMG for sprite" << std::endl;
	}
}

// Draws the texture to a rectangle with the current sprite attributes
void Sprite::draw() {
	SDL_QueryTexture(this->imageTexture, NULL, NULL, NULL, NULL);
	SDL_Rect textureRec = { this->x, this->y, this->width, this->height };
	SDL_RenderCopyEx(this->renderer, this->imageTexture, NULL, &textureRec, this->angle, NULL, SDL_FLIP_NONE);
}

void Sprite::setX(int x) {
	this->x = x;
}

void Sprite::setY(int y) {
	this->y = y;
}

int Sprite::getX() {
	return this->x;
}

int Sprite::getY() {
	return this->y;
}

void Sprite::changeXBy(int dx) {
	this->x += dx;
}

void Sprite::changeYBy(int dy) {
	this->y += dy;
}

int Sprite::getWidth() {
	return this->width;
}

int Sprite::getHeight() {
	return this->height;
}

void Sprite::setAngle(double angle) {
	this->angle = angle;
}

// Checks for a collision between this sprite and the sprite passed in
bool Sprite::isCollidingWith(Sprite sprite) {
	int left = this->x - (this->width / 2);
	int right = this->x + (this->width / 2);
	int top = this->y - (this->height / 2);
	int bottom = this->y + (this->height / 2);
	int spriteLeft = sprite.getX() - (sprite.getWidth() / 2);
	int spriteRight = sprite.getX() + (sprite.getWidth() / 2);
	int spriteTop = sprite.getY() - (sprite.getHeight() / 2);
	int spriteBottom = sprite.getY() + (sprite.getHeight() / 2);
	
	if ((bottom < spriteTop) || 
		(top > spriteBottom) ||
		(right < spriteLeft) ||
		(left > spriteRight)) {
		return false;
	}
	return true;
}

SDL_Texture *Sprite::getTexture() {
	return this->imageTexture;
}