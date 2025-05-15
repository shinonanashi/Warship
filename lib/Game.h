#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Texture.h"
#include "RenderWindow.h"
#include "ObjectSpawner.h"
#include "UIManager.h"


class Game
{
public:
	Game();

	void Init();
	void HandleEvent();
	void Update();
	void CheckCollision();
	void Render();
	void Clean();

	bool Running() { return isRunning; }


private:
	bool isRunning;
	bool mouseButtonDown;
    SDL_Texture* background;
	int mouseX;
	int mouseY;

	RenderWindow window;
};
