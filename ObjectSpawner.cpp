

#include "lib/ObjectSpawner.h"
#include "lib/UIManager.h"


ObjectSpawner::ObjectSpawner()
{
	maxTime = 3;

	StrightSpawnPositions = Vector2f(50, -10);
}

ObjectSpawner& ObjectSpawner::GetInstance()
{
	static ObjectSpawner* instance = new ObjectSpawner;

	return *instance;
}

void ObjectSpawner::Update()
{
	RemoveEnemies();

	if (!m_SpawnEnemyTimer.IsStarted() && UIManager::GetInstance().m_gameState == UIManager::GetInstance().Playing)
		m_SpawnEnemyTimer.Start();
	else if (UIManager::GetInstance().m_gameState != UIManager::GetInstance().Playing)
		m_SpawnEnemyTimer.Stop();

	if (UIManager::GetInstance().m_gameState == UIManager::GetInstance().Playing)
		SpawnEnemies();


	if (UIManager::GetInstance().m_gameState != UIManager::GetInstance().Menu)
	{

		for (int i = 0; i < smallEnemies.size(); i++)
			smallEnemies[i].Update();

		for (int i = 0; i < mediumEnemies.size(); i++)
			mediumEnemies[i].Update();

		for (int i = 0; i < bigEnemies.size(); i++)
			bigEnemies[i].Update();

		m_FirstAid.Update();
		m_Shield.Update();

		for (int i = 0; i < hitMarkers.size(); i++)
		{
			hitMarkers[i].SetScale(Vector2f(Mathf::Lerp(hitMarkers[i].GetScale().x, -0.05, 0.05), Mathf::Lerp(hitMarkers[i].GetScale().y, -0.05, 0.05)));

			if (hitMarkers[i].GetScale().x <= 0)
				hitMarkers.erase(hitMarkers.begin() + i);
		}

		for (int i = 0; i < blastEffect.size(); i++)
		{
			blastEffect[i].SetScale(Vector2f(Mathf::Lerp(blastEffect[i].GetScale().x, -0.05, 0.05), Mathf::Lerp(blastEffect[i].GetScale().y, -0.05, 0.05)));

			if (blastEffect[i].GetScale().x <= 0)
				blastEffect.erase(blastEffect.begin() + i);
		}

		for (int i = 0; i < smokeEffect.size(); i++)
		{
			smokeEffect[i].SetScale(Vector2f(Mathf::Lerp(smokeEffect[i].GetScale().x, -0.05, 0.0075), Mathf::Lerp(smokeEffect[i].GetScale().y, -0.05, 0.0075)));

			if (smokeEffect[i].GetScale().x <= 0)
				smokeEffect.erase(smokeEffect.begin() + i);
		}
	}
}

void ObjectSpawner::SpawnEnemies()
{

	if (m_SpawnEnemyTimer.GetTicks() * 0.001 > maxTime)
	{
		int rand = Mathf::Random(1, 100);

		if (rand <= 50)
			SpawnSmallEnemies(Vector2f(Mathf::Random(50, 650), -10));

		else if (rand <= 93 && rand > 50)
			SpawnMediumEnemies(Vector2f(Mathf::Random(50, 650), -10));

		else if (rand <= 95 && rand > 93)
			SpawnBigEnemies(Vector2f(Mathf::Random(50, 650), -10));
		else
			SpawnPartten();

		m_SpawnEnemyTimer.Stop();
	}
}

void ObjectSpawner::SpawnSmallEnemies(Vector2f p_pos)
{
	int rand = Mathf::Random(1, 3);
	SmallEnemy temp(p_pos, Texture::GetInstance().smallEnemyShips[rand - 1], Vector2f(1.75, 1.75), rand);

	smallEnemies.push_back(temp);
}

void ObjectSpawner::SpawnMediumEnemies(Vector2f p_pos)
{
	int rand = Mathf::Random(1, 3);
	MediumEnemy temp(p_pos, Texture::GetInstance().mediumEnemyShips[rand - 1], Vector2f(1.9, 1.9), rand);

	mediumEnemies.push_back(temp);

}

void ObjectSpawner::SpawnBigEnemies(Vector2f p_pos)
{
	int rand = Mathf::Random(1, 3);
	BigEnemy temp(p_pos, Texture::GetInstance().bigEnemyShips[rand - 1], Vector2f(2.2, 2.2), rand);

	bigEnemies.push_back(temp);
}

void ObjectSpawner::SpawnHitMarkers(Vector2f p_Pos)
{
	Entity temp(p_Pos, Texture::GetInstance().hitMark[Mathf::Random(0, 2)], Vector2f(2, 2));

	hitMarkers.push_back(temp);
}

void ObjectSpawner::SpawnBlastEffect(Vector2f p_Pos, Vector2f p_Scale)
{
	Entity temp(p_Pos, Texture::GetInstance().blastEffect, p_Scale);

	blastEffect.push_back(temp);
}

void ObjectSpawner::SpawnSmokEffect(Vector2f p_Pos, Vector2f p_Scale)
{
	Entity temp(p_Pos, Texture::GetInstance().smokeEffect, p_Scale);

	smokeEffect.push_back(temp);
}

void ObjectSpawner::SpawnFirstAid(Vector2f p_Pos, Vector2f p_Scale)
{
	Entity temp(p_Pos, Texture::GetInstance().firstAid, p_Scale);

	m_FirstAid = temp;
}

void ObjectSpawner::SpawnShield(Vector2f p_Pos, Vector2f p_Scale)
{
	Entity temp(p_Pos, Texture::GetInstance().shield, p_Scale);

	m_Shield = temp;
}

void ObjectSpawner::SpawnPartten()
{
	int rand = Mathf::Random(150, 600);

	SpawnBigEnemies(Vector2f(rand, -20));
	SpawnSmallEnemies(Vector2f(rand + 80, -10));
	SpawnSmallEnemies(Vector2f(rand - 80, -10));
}

void ObjectSpawner::RemoveEnemies()
{

	for (int i = 0; i < smallEnemies.size(); i++)
		if (smallEnemies[i].IsDestroy() && smallEnemies[i].GetProjectiles().empty())
			smallEnemies.erase(smallEnemies.begin() + i);

	for (int i = 0; i < mediumEnemies.size(); i++)
		if (mediumEnemies[i].IsDestroy() && mediumEnemies[i].GetProjectiles().empty())
			mediumEnemies.erase(mediumEnemies.begin() + i);

	for (int i = 0; i < bigEnemies.size(); i++)
		if (bigEnemies[i].IsDestroy() && bigEnemies[i].GetProjectiles().empty() && bigEnemies[i].GetMissiles().IsDestroy())
			bigEnemies.erase(bigEnemies.begin() + i);
}

Entity& ObjectSpawner::GetFirstAid()
{
	return m_FirstAid;
}

Entity& ObjectSpawner::GetShield()
{
	return m_Shield;
}

std::vector<SmallEnemy>& ObjectSpawner::GetSmallEnemies()
{
	return smallEnemies;
}

std::vector<MediumEnemy>& ObjectSpawner::GetMediumEnemies()
{
	return mediumEnemies;
}

std::vector<BigEnemy>& ObjectSpawner::GetBigEnemies()
{
	return bigEnemies;
}

std::vector<Entity>& ObjectSpawner::GetHitMarkers()
{
	return hitMarkers;
}

void ObjectSpawner::Render(RenderWindow& window)
{

	for (int i = 0; i < smallEnemies.size(); i++)
	{
		smallEnemies[i].Render(window);

		if (!smallEnemies[i].IsDestroy())
			window.Render(smallEnemies[i], 180, true);
	}

	for (int i = 0; i < mediumEnemies.size(); i++)
	{
		mediumEnemies[i].Render(window);

		if (!mediumEnemies[i].IsDestroy())
			window.Render(mediumEnemies[i], 180, true);

	}

	for (int i = 0; i < bigEnemies.size(); i++)
	{
		bigEnemies[i].Render(window);

		if (!bigEnemies[i].IsDestroy())
			window.Render(bigEnemies[i], 180, false);

	}

	for (int i = 0; i < hitMarkers.size(); i++)
		window.Render(hitMarkers[i], 0, false);

	for (int i = 0; i < smokeEffect.size(); i++)
		window.Render(smokeEffect[i], 0, false);

	for (int i = 0; i < blastEffect.size(); i++)
		window.Render(blastEffect[i], 0, false);

	if (!m_FirstAid.IsDestroy())
		window.Render(m_FirstAid, 0, false);

	if (!m_Shield.IsDestroy())
		window.Render(m_Shield, 0, false);
}
