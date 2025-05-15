#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"
#include "Missile.h"
#include "Timer.h"
#include "Flare.h"


class Player : public Entity
{
public:
	Player() = default;
	Player(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale);
	void Update();
	void HandleEvent(SDL_Event event);
	void Render(RenderWindow& window);
	void Shoot();
	void ShootMissile();
	void ShootFlares();
	void RemoveUnwantedStuff();
	void SetPlayerMissileTarget(Vector2f* p_Target);
	void Damage(int damage);
	void SetHitPoints(int p_HitPoints);
	void SetShield(int p_Shield);

	std::vector<Projectile>& GetPlayerProjectiles();
	Missile& GetMissile();
	std::vector<Flare>& GetFlares();
	int GetHitPoints();
	int GetShield();

	bool once;
	bool missileCoolDown;
	bool flareCoolDown;

private:
	float m_Speed;
	float maxTime;
	float previousTime;
	float m_MissileMaxTime;
	float m_FlaresMaxTime;
	float m_FlaresCoolDownMaxTime;
	float missileAngle;

	int flareCounter;
	int hitPoints;
	int shield;

	bool shootCoolDown;
	bool shootFlare;
	bool shieldActive;

	Vector2f originalScale;
	Vector2f* m_Target;

	std::vector<Projectile> projectiles;
	std::vector<Flare> flares;

	Missile missile;

	Timer m_MissileTimer;
	Timer m_FlareTimer;
	Timer m_FlareCoolDownTimer;
};
