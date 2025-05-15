
#include <SDL.h>
#include <SDL_image.h>

#include "lib/Entity.h"
#include "lib/Game.h"

Game game;

int main(int argc, char* args[])
{
	const int fps = 120;
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	game.Init();

	while (game.Running())
	{
		frameStart = SDL_GetTicks();

		game.Update();
		game.HandleEvent();
		game.Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	game.Clean();

	return 0;
}
