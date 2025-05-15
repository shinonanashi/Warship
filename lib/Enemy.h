#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Missile.h"
#include "Projectile.h"


class Enemy : public Entity
{
public:
	Enemy() = default;
	Enemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale);
	void Update();
	void Render(RenderWindow& window);
	void Shoot(float p_bulletOffset, int p_bulletPair);
	void Damage(int value);
	void RemoveProjectiles();


	std::vector<Projectile>& GetProjectiles();

protected:
	float m_Speed;
	float m_OriginalFireRate;
	float m_CurrentFireRate;
	float m_ShootDelay;
	float previousTime;
	float m_BulletOffset;

	int counter;
	int m_bulletPair;
	int m_noOfBullets;
	int hitPoints;

	std::string m_Tag;

	bool shootCoolDown;

	Vector2f originalScale;

	std::vector<Projectile> projectiles;
};
