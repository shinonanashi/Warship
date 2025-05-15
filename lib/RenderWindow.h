#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Entity.h"


class RenderWindow
{
public:
	RenderWindow(const char* p_title, int x, int y, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void Render(Entity& p_entity, float angle, bool animate);
	void RenderText(Vector2f p_pos, std::string p_text, TTF_Font* font, SDL_Color textColor);
	void display();
	void renderBackground(SDL_Texture* backgroundTex);
	SDL_Renderer* GetRenderer();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

};
