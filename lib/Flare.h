#pragma once
#include "Entity.h"

class Flare : public Entity
{
public:
	Flare() = default;
	Flare(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int dir, float angle);
	void Update();

	float m_Angle;

private:
	float m_Speed;

	int m_Dir;
};
