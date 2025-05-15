#include "lib/BigEnemy.h"
#include "lib/UIManager.h"

BigEnemy::BigEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType)
	:Enemy(p_pos, p_tex, p_scale)
{
	m_Tag = "BigEnemy";

	missileAngle = 180;
	m_MissileMaxTime = 10;

	missileCoolDown = false;

	DefineShipType(p_shipType);

	m_CurrentFireRate = m_OriginalFireRate;
}

void BigEnemy::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(1);

	if (!Texture::GetInstance().m_PlayerShip.GetFlares().empty())
	{
		for (int i = 0; i < Texture::GetInstance().m_PlayerShip.GetFlares().size(); i++)
		{
			if (!Texture::GetInstance().m_PlayerShip.GetFlares()[i].IsDestroy())
			{
				m_Target = &Texture::GetInstance().m_PlayerShip.GetFlares()[i].GetPos();
				break;
			}
		}
	}
	else
		m_Target = &Texture::GetInstance().m_PlayerShip.GetPos();


	missile.Update(*m_Target);

	if (!m_MissileTimer.IsStarted())
		m_MissileTimer.Start();

	if (m_MissileTimer.GetTicks() * 0.001 >= m_MissileMaxTime && missile.IsDestroy())
	{
		missileCoolDown = false;
		m_MissileTimer.Stop();
	}


	RemoveProjectiles();

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

	SetScale(Vector2f(Mathf::Lerp(GetScale().x, originalScale.x, 0.1), Mathf::Lerp(GetScale().y, originalScale.y, 0.5)));

	if (GetPos().y >= 740)
		Destroy();

	Shoot(m_BulletOffset, m_bulletPair);

	if(UIManager::GetInstance().m_gameState == UIManager::GetInstance().Playing)
		ShootMissiles();


	SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

}

void BigEnemy::Shoot(float p_bulletOffset, int p_bulletPair)
{
	if (shootCoolDown)
		return;

	shootCoolDown = true;
	counter++;

	for (int i = 0; i < p_bulletPair; i++)
	{
		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Shoot);

		Projectile temp1(Vector2f(GetPos().x + m_BulletOffset * (i % 2 == 0 ? 1 : -1), GetPos().y), Texture::GetInstance().projectile01, Vector2f(0.9, 0.9));
		Projectile temp2(Vector2f(temp1.GetPos().x + 8 * (i % 2 == 0 ? 1 : -1), GetPos().y), Texture::GetInstance().projectile01, Vector2f(0.9, 0.9));

		projectiles.push_back(temp1);
		projectiles.push_back(temp2);
	}


}

void BigEnemy::ShootMissiles()
{
	if (!missileCoolDown)
	{
		missileCoolDown = true;

		Missile temp(Vector2f(GetPos().x, GetPos().y), Texture::GetInstance().missile, Vector2f(2, 2));

		missile = temp;
	}
}

void BigEnemy::DefineShipType(int type)
{
	switch (type)
	{
	case 1:
		m_shipType = QuardShooter_SingleMissile_Slower;
		m_BulletOffset = 16;
		m_bulletPair = 2;
		m_Speed = 0.2;
		m_OriginalFireRate = 0.1;
		m_noOfBullets = 7;
		m_ShootDelay = 3;
		hitPoints = 24;
		break;

	case 2:
		m_shipType = QuardShooter_DoubleMissile_Faster;
		m_BulletOffset = 16;
		m_bulletPair = 2;
		m_Speed = 0.35;
		m_OriginalFireRate = 0.15;
		m_noOfBullets = 3;
		m_ShootDelay = 2;
		hitPoints = 18;
		break;

	case 3:
		m_shipType = Faster;
		m_BulletOffset = 16;
		m_bulletPair = 2;
		m_Speed = 0.4;
		m_OriginalFireRate = 0.2;
		m_noOfBullets = 2;
		m_ShootDelay = 1;
		hitPoints = 18;
		break;

	default:
		break;
	}
}

Missile& BigEnemy::GetMissiles()
{
	return missile;
}

void BigEnemy::Render(RenderWindow& window) {

	Enemy::Render(window);

	if (!missile.IsDestroy())
	{
		missileAngle = atan2(m_Target->y - missile.GetPos().y, m_Target->x - missile.GetPos().x) * 180.0f / 3.14f + 90;
		window.Render(missile, missileAngle, false);
	}


}
