#pragma once
#include <SDL2/SDL_image.h>

class Sprite
{
public:
	Sprite(SDL_Renderer *renderer, const char *filename, int width, int height);
	void draw();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void changeXBy(int dx);
	void changeYBy(int dy);
	int getWidth();
	int getHeight();
	void setAngle(double angle);
	bool isCollidingWith(Sprite sprite);
	SDL_Texture *getTexture();

private:
	SDL_Renderer *renderer;
	SDL_Texture *imageTexture;
	int width;
	int height;
	int x;
	int y;
	double angle;
};