#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"


class SmallEnemy : public Enemy
{
public:
	SmallEnemy() = default;
	SmallEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType);
	void DefineShipType(int type);

private:

	enum ShipType
	{
		SingleShooter,
		DoubleShooter,
		Faster
	};

	ShipType m_shipType;
};
