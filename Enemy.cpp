#include "lib/Enemy.h"
#include "lib/Mathf.h"
#include "lib/ObjectSpawner.h"
#include "lib/UIManager.h"
#include <cstring>



Enemy::Enemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	previousTime = 0;

	counter = 0;

	shootCoolDown = false;

	originalScale = p_scale;

	m_CurrentFireRate = m_OriginalFireRate;
}

void Enemy::Update()
{
	RemoveProjectiles();

	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(1);


	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].GetPos().y >= 730)
			projectiles[i].Destroy();
	}

	if (IsDestroy())
		return;

	Entity::Update();


	if (SDL_GetTicks() * 0.001 - previousTime >= m_CurrentFireRate && shootCoolDown)
	{
		previousTime = SDL_GetTicks() * 0.001;
		shootCoolDown = false;

		if (counter == m_noOfBullets)
		{
			m_CurrentFireRate = m_ShootDelay;
			counter = 0;
		}
		else if (counter < m_noOfBullets)
			m_CurrentFireRate = m_OriginalFireRate;
	}

	if (GetPos().y >= 740)
		Destroy();

	SetScale(Vector2f(Mathf::Lerp(GetScale().x, originalScale.x, 0.1), Mathf::Lerp(GetScale().y, originalScale.y, 0.1)));

	Shoot(m_BulletOffset, m_bulletPair);

	SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

}

void Enemy::Shoot(float p_bulletOffset, int p_bulletPair)
{
	if (shootCoolDown)
		return;

	shootCoolDown = true;
	counter++;

	for (int i = 0; i < p_bulletPair; i++)
	{
		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Shoot);

		Projectile temp(Vector2f(GetPos().x + m_BulletOffset * (i % 2 == 0 ? 1 : -1), GetPos().y), Texture::GetInstance().projectile01, Vector2f(0.9, 0.9));

		projectiles.push_back(temp);
	}

}

void Enemy::RemoveProjectiles()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].IsDestroy())
		{
			projectiles.erase(projectiles.begin() + i);
		}
	}
}

void Enemy::Damage(int value)
{
	SetScale(Vector2f(originalScale.x + 0.3, originalScale.y + 0.3));

	hitPoints -= value;

	if (hitPoints <= 0)
	{
		Destroy();
		ObjectSpawner::GetInstance().SpawnBlastEffect(GetPos(), Vector2f(8, 8));
		ObjectSpawner::GetInstance().SpawnSmokEffect(GetPos(), Vector2f(8, 8));

		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Explosion);

		UIManager::GetInstance().SetKills(1);

		if(std::strcmp(m_Tag.c_str(), "BigEnemy") == 0)
		{
			UIManager::GetInstance().UpdateScore(15);

			if(Mathf::Random(0, 100) > 70)
				ObjectSpawner::GetInstance().SpawnFirstAid(GetPos(), Vector2f(2, 2));
			else if(Mathf::Random(0, 100) > 70)
				ObjectSpawner::GetInstance().SpawnShield(GetPos(), Vector2f(2, 2));
		}
		else if (std::strcmp(m_Tag.c_str(), "MediumEnemy") == 0)
		{
			UIManager::GetInstance().UpdateScore(8);

			if (Mathf::Random(0, 100) > 90)
				ObjectSpawner::GetInstance().SpawnFirstAid(GetPos(), Vector2f(2, 2));
			else if (Mathf::Random(0, 100) > 90)
				ObjectSpawner::GetInstance().SpawnShield(GetPos(), Vector2f(2, 2));
		}
		else
		{
			UIManager::GetInstance().UpdateScore(4);

			if (Mathf::Random(0, 100) > 95)
				ObjectSpawner::GetInstance().SpawnFirstAid(GetPos(), Vector2f(2, 2));
			else if (Mathf::Random(0, 100) > 95)
				ObjectSpawner::GetInstance().SpawnShield(GetPos(), Vector2f(2, 2));
		}

	}
}

std::vector<Projectile>& Enemy::GetProjectiles()
{
	return projectiles;
}


void Enemy::Render(RenderWindow& window) {

	for (int i = 0; i < projectiles.size(); i++)
		if(!projectiles[i].IsDestroy())
			window.Render(projectiles[i], 0, false);
}
