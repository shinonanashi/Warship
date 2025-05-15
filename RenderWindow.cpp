
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "lib/RenderWindow.h"
#include "lib/Entity.h"



RenderWindow::RenderWindow(const char* p_title, int x, int y, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer,p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}
void RenderWindow::renderBackground(SDL_Texture* backgroundTex)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(backgroundTex, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    dst.w = 720;
    dst.h = 720;
    SDL_RenderCopy(renderer, backgroundTex, &src, &dst);
}


void RenderWindow::Render(Entity& p_entity, float angle, bool animate)
{
	SDL_Rect src;

	src.x = 0;
	src.y = 0;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.GetPos().x - src.w / 2 * p_entity.GetScale().x;
	dst.y = p_entity.GetPos().y - src.h / 2 * p_entity.GetScale().y;
	dst.w = src.w * p_entity.GetScale().x;
	dst.h = src.h * p_entity.GetScale().y;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, angle, NULL, SDL_FLIP_NONE);
}

void RenderWindow::RenderText(Vector2f p_pos, std::string p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, p_text.c_str(), textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;

	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h;

	SDL_Rect dst;
	dst.x = p_pos.x - src.w / 2;
	dst.y = p_pos.y - src.h / 2;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}



void RenderWindow::display()
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::GetRenderer()
{
	return renderer;
}

