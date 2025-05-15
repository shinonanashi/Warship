#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"
#include "Missile.h"
#include "Enemy.h"
#include"Texture.h"
#include "Timer.h"

class BigEnemy : public Enemy
{
public:
	BigEnemy() = default;
	BigEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType);
	void Update();
	void Render(RenderWindow& window);
	void Shoot(float p_bulletOffset, int p_bulletPair);
	void ShootMissiles();
	Missile& GetMissiles();
	void DefineShipType(int type);

private:

	float missileAngle;
	float m_MissileMaxTime;

	enum ShipType
	{
		QuardShooter_SingleMissile_Slower,
		QuardShooter_DoubleMissile_Faster,
		Faster
	};

	ShipType m_shipType;

	bool missileCoolDown;

	Missile missile;

	Timer m_MissileTimer;

	Vector2f* m_Target;
};
