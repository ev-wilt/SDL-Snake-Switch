#include "Sprite.h"
#include "Snake.h"
#include "Food.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <switch.h>

#define BUTTON_PLUS 10

// Event Queue
std::vector<SDL_Event> &getEvents()
{
	static std::vector<SDL_Event> events;
	return events;
}

void initJoycons() {
        for (int i = 0; i < 2; i++) {
        if (SDL_JoystickOpen(i) == NULL) {
            std::cerr << SDL_GetError() << std::endl;
            SDL_Quit();
        }
    }
}

int main(int argc, char *argv[]) {

	// Inital Setup

	atexit(SDL_Quit);
	Result rc = romfsInit();
    if (R_FAILED(rc)) {
		std::cerr << rc << std::endl;
	}
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
		std::cerr << SDL_GetError() << std::endl;
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cerr << IMG_GetError() << std::endl;
	}
	SDL_Window *win = NULL;
	SDL_Renderer* renderer = NULL;
    SDL_CreateWindowAndRenderer(1280, 720, 0, &win, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	Snake player = Snake(renderer);
	Food food = Food(renderer, 40, 40);
	Sprite background = Sprite(renderer, "romfs:/assets/background.png", 1280, 720);
	initJoycons();

	// Game Loop
	unsigned short updateCounter = 0;
    while(true) {

		// Save user input to a queue
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			getEvents().push_back(e);
		}

		for (long unsigned int i = 0; i < getEvents().size(); ++i) {
			if (getEvents()[i].type == SDL_JOYBUTTONDOWN) {
				switch (getEvents()[i].jbutton.button) {
				case BUTTON_PLUS:
					exit(0);
					break;

				default:
					break;
				}
			}
		}

		// Do sprite updates every 20 ticks
		player.checkInput(getEvents(), updateCounter);
		if (updateCounter == 20) {
			player.update();
			if (player.ateFood(food)) {
				while (player.isCollidingWith(food)) {
					food.resetPosition();
				}
				player.increaseSize(renderer);
			}
			updateCounter = 0;
		}

		// Draw to renderer
		background.draw();
		food.draw();
		player.draw();
		SDL_RenderPresent(renderer);
		getEvents().clear();
		updateCounter++;
	}
	consoleExit(NULL);
	return 0;
}