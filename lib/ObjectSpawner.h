#pragma once
#include <vector>
#include <iostream>

#include "Entity.h"
#include "RenderWindow.h"
#include "SmallEnemy.h"
#include "MediumEnemy.h"
#include "BigEnemy.h"
#include "Texture.h"
#include "Timer.h"


class ObjectSpawner
{
public:
	ObjectSpawner();

	static ObjectSpawner& GetInstance();

	void Update();
	void Render(RenderWindow& window);
	void SpawnEnemies();
	void SpawnSmallEnemies(Vector2f p_pos);
	void SpawnMediumEnemies(Vector2f p_pos);
	void SpawnBigEnemies(Vector2f p_pos);
	void SpawnPartten();
	void RemoveEnemies();
	void SpawnHitMarkers(Vector2f p_Pos);
	void SpawnBlastEffect(Vector2f p_Pos, Vector2f p_Scale);
	void SpawnSmokEffect(Vector2f p_Pos, Vector2f p_Scale);
	void SpawnFirstAid(Vector2f p_Pos, Vector2f p_Scale);
	void SpawnShield(Vector2f p_Pos, Vector2f p_Scale);

	std::vector<SmallEnemy>& GetSmallEnemies();
	std::vector<MediumEnemy>& GetMediumEnemies();
	std::vector<BigEnemy>& GetBigEnemies();

	std::vector<Entity>& GetHitMarkers();

	Entity& GetFirstAid();
	Entity& GetShield();

private:
	float maxTime;

	Vector2f StrightSpawnPositions;

	std::vector<SmallEnemy> smallEnemies;
	std::vector<MediumEnemy> mediumEnemies;
	std::vector<BigEnemy> bigEnemies;

	std::vector<Entity> hitMarkers;
	std::vector<Entity> blastEffect;
	std::vector<Entity> smokeEffect;

	Entity m_FirstAid;
	Entity m_Shield;

	Timer m_SpawnEnemyTimer;

};
