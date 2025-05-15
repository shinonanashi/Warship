#pragma once
#include "Entity.h"

class Missile : public Entity
{
public:
	Missile() = default;
	Missile(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale);
	void Update(Vector2f target);

	bool followTarget;

private:
	float m_Speed;
	float maxTime;
	float currentTime;

	Vector2f direction;

};
