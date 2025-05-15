#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Mathf.h"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale);
	Entity() = default;

	Vector2f& GetPos()
	{
		return pos;
	}

	Vector2f& GetScale()
	{
		return scale;
	}

	void SetPos(Vector2f pos);
	void SetScale(Vector2f scale);
	void Update();
	void Destroy();
	void SetDestroyFalse();

	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	SDL_Rect& GetDst();

	bool IsDestroy();

private:
	Vector2f pos;
	Vector2f scale;

	SDL_Rect currentFrame;
	SDL_Rect dst;
	SDL_Texture* tex;

	bool destroy;
};
