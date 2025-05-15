#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile() = default;
	Projectile(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale);
	void Update(int dir);
private:
	float m_Speed;
};
