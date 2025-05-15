#include <SDL.h>
#include <SDL_image.h>

#include "lib/Entity.h"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:pos(p_pos), tex(p_tex), scale(p_scale)
{
	SDL_QueryTexture(tex, NULL, NULL, &currentFrame.w, &currentFrame.h);

	currentFrame.x = 0;
	currentFrame.y = 0;

	destroy = false;
}

void Entity::Update()
{
	dst.x = GetPos().x - currentFrame.w / 2 * GetScale().x;
	dst.y = GetPos().y - currentFrame.h / 2 * GetScale().y;
	dst.w = GetScale().x * currentFrame.w;
	dst.h = GetScale().y * currentFrame.h;
}

void Entity::SetPos(Vector2f _pos)
{
	pos = _pos;
}

void Entity::SetScale(Vector2f _scale)
{
	scale = _scale;
}

void Entity::Destroy()
{
	destroy = true;
}

void Entity::SetDestroyFalse()
{
	destroy = false;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

SDL_Rect& Entity::GetDst()
{
	return dst;
}

bool Entity::IsDestroy()
{
	return  destroy;
}
