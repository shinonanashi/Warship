
#include "lib/Player.h"
#include "lib/Texture.h"
#include "lib/ObjectSpawner.h"
#include "lib/UIManager.h"

Player::Player(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 1.5;

	previousTime = 0;
	maxTime = 0.2;

	shootCoolDown = false;
	missileCoolDown = false;
	flareCoolDown = false;
	shootFlare = false;
	shieldActive = false;

	once = true;

	m_MissileMaxTime = 7;
	m_FlaresMaxTime = 0.1;
	m_FlaresCoolDownMaxTime = 10;

	hitPoints = 50;
	shield = 0;
	flareCounter = 0;

	originalScale = Vector2f(2.25, 2.25);

}

void Player::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(-1);

	for (int i = 0; i < flares.size(); i++)
		flares[i].Update();

	if (!missile.IsDestroy() && !once)
		missile.Update(*m_Target);

	if (!IsDestroy())
	{
		Entity::Update();

		if (GetPos().y >= 690)
			SetPos(Vector2f(GetPos().x, 690));
		else if (GetPos().y <= 30)
			SetPos(Vector2f(GetPos().x, 30));

		if (GetPos().x >= 690)
			SetPos(Vector2f(690, GetPos().y));
		else if (GetPos().x <= 30)
			SetPos(Vector2f(30, GetPos().y));


		if (SDL_GetTicks() * 0.001 - previousTime >= maxTime && shootCoolDown)
		{
			previousTime = SDL_GetTicks() * 0.001;
			shootCoolDown = false;
		}

		if (!m_MissileTimer.IsStarted() && missileCoolDown)
			m_MissileTimer.Start();

		if (m_MissileTimer.GetTicks() * 0.001 >= m_MissileMaxTime)
		{
			AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_MissileReady);
			missileCoolDown = false;
			m_MissileTimer.Stop();
		}

		if (!m_FlareCoolDownTimer.IsStarted() && flareCoolDown)
			m_FlareCoolDownTimer.Start();

		if (m_FlareCoolDownTimer.GetTicks() * 0.001 >= m_FlaresCoolDownMaxTime)
		{
			AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_FlaresReady);
			flareCoolDown = false;
			m_FlareCoolDownTimer.Stop();
		}

		if (missile.IsDestroy())
			once = true;

		SetScale(Vector2f(Mathf::Lerp(GetScale().x, originalScale.x, 0.1), Mathf::Lerp(GetScale().y, originalScale.y, 0.1)));

		if (shootFlare)
		{
			ShootFlares();
		}

		RemoveUnwantedStuff();
	}
}

void Player::HandleEvent(SDL_Event event)
{
	if (!IsDestroy())
	{
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (currentKeyStates[SDL_SCANCODE_A])
			SetPos(Vector2f(GetPos().x - m_Speed, GetPos().y));

		else if (currentKeyStates[SDL_SCANCODE_D])
			SetPos(Vector2f(GetPos().x + m_Speed, GetPos().y));

		if (currentKeyStates[SDL_SCANCODE_W])
			SetPos(Vector2f(GetPos().x, GetPos().y - m_Speed));

		else if (currentKeyStates[SDL_SCANCODE_S])
			SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

		if (currentKeyStates[SDL_SCANCODE_E] && !flareCoolDown)
			shootFlare = true;

		if (currentKeyStates[SDL_SCANCODE_SPACE])
			Shoot();

		if (event.type == SDL_MOUSEBUTTONDOWN)
			ShootMissile();
	}
}

void Player::Shoot()
{
	if (!shootCoolDown)
	{
		shootCoolDown = true;

		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Shoot);

		Projectile temp(Vector2f(GetPos().x, GetPos().y), Texture::GetInstance().projectile01, Vector2f(1, 1));

		projectiles.push_back(temp);

	}
}

void Player::ShootMissile()
{
	if (!missileCoolDown && Texture::GetInstance().isCursorCollideWithEnemy)
	{
		missileCoolDown = true;
		Missile temp(Vector2f(GetPos().x, GetPos().y), Texture::GetInstance().missile, Vector2f(2, 2));

		missile = temp;
	}
}

void Player::ShootFlares()
{
	if (!m_FlareTimer.IsStarted())
		m_FlareTimer.Start();

	if (!flareCoolDown && m_FlareTimer.GetTicks() * 0.001 >= m_FlaresMaxTime)
	{
		flareCounter++;

		Flare temp(Vector2f(GetPos().x, GetPos().y), Texture::GetInstance().flare, Vector2f(1.75, 1.75), flareCounter % 2 == 0 ? 1 : -1, flareCounter % 2 == 0 ? 100 : -100);
		ObjectSpawner::GetInstance().SpawnSmokEffect(Vector2f(GetPos().x, GetPos().y), Vector2f(5, 5));

		flares.push_back(temp);
		m_FlareTimer.Stop();

		if (flareCounter >= 8)
		{
			shootFlare = false;
			flareCoolDown = true;
			flareCounter = 0;
		}
	}
}

void Player::Damage(int damage)
{
	SetScale(Vector2f(originalScale.x + 0.3, originalScale.y + 0.3));


	if (shield <= 0)
	{
		hitPoints -= damage;
		UIManager::GetInstance().UpdateHealthBar(damage);
	}
	else
	{
		shield -= damage;
		UIManager::GetInstance().UpdateShieldBar(damage);
	}

	if (hitPoints <= 0)
	{
		Destroy();

		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Explosion);

		ObjectSpawner::GetInstance().SpawnBlastEffect(GetPos(), Vector2f(8, 8));
		ObjectSpawner::GetInstance().SpawnSmokEffect(GetPos(), Vector2f(8, 8));

		UIManager::GetInstance().m_gameState = UIManager::GetInstance().GameOver;
	}
}

void Player::SetHitPoints(int p_HitPoints)
{
	hitPoints = p_HitPoints;
}

void Player::SetShield(int p_Shield)
{
	shield = p_Shield;
}


void Player::RemoveUnwantedStuff()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].GetPos().y <= -10)
			projectiles[i].Destroy();

		if (projectiles[i].IsDestroy())
			projectiles.erase(projectiles.begin() + i);

	}

	for (int i = 0; i < flares.size(); i++)
	{
		if (flares[i].GetPos().y >= 730 || flares[i].GetPos().x >= 730 || flares[i].GetPos().x <= -10)
			flares[i].Destroy();

		if (flares[i].IsDestroy())
			flares.erase(flares.begin() + i);

	}
}

std::vector<Projectile>& Player::GetPlayerProjectiles()
{
	return projectiles;
}

Missile& Player::GetMissile()
{
	return missile;
}

std::vector<Flare>& Player::GetFlares()
{
	return flares;
}

void Player::SetPlayerMissileTarget(Vector2f* p_Target)
{
	m_Target = p_Target;
}

int Player::GetHitPoints()
{
	return hitPoints;
}

int Player::GetShield()
{
	return shield;
}

void Player::Render(RenderWindow& window) {

	for (int i = 0; i < projectiles.size(); i++)
		if(!projectiles[i].IsDestroy())
			window.Render(projectiles[i], 0, false);

	if (!missile.IsDestroy() && !once)
	{
		missileAngle = atan2(m_Target->y - missile.GetPos().y, m_Target->x - missile.GetPos().x) * 180.0f / 3.14f + 90;

		window.Render(missile, missileAngle, false);
	}

	for (int i = 0; i < flares.size(); i++)
		if (!flares[i].IsDestroy())
			window.Render(flares[i], flares[i].m_Angle, false);
}

