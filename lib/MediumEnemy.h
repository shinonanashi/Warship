#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"
#include "Enemy.h"


class MediumEnemy : public Enemy
{
public:
	MediumEnemy() = default;
	MediumEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType);
	void DefineShipType(int type);

private:

	enum ShipType
	{
		DoubleShooter_Slower,
		DoubleShooter_Faster,
		Faster
	};

	ShipType m_shipType;
};
