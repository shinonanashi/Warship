#pragma once
#include "Texture.h"
#include "Timer.h"
#include "AudioManager.h"


class UIManager
{
public:
	UIManager();

	static UIManager& GetInstance();

	void Update();
	void HandleEvent(SDL_Event event);

	void PositionAndScalingUI();
	void CheckUICollision();
	void UpdateHealthBar(int damage);
	void UpdateShieldBar(int damage);
	void UpdateScore(int p_Score);
	void Reset();

	void SetRenderer(SDL_Renderer* renderer);
	void SetKills(int p_Kills);
	void ResetHealthBar();
	void ResetShieldBar();

	void Render(RenderWindow& window);

	enum GameState
	{
		Menu,
		Playing,
		GameOver
	};

	GameState m_gameState;

	bool m_Exit;


private:

	std::string m_MissileText;
	std::string m_FlareText;

	std::string m_ScoreText;

	int m_Score;
	int m_Kills;

	bool m_mouseButtonDown;
	bool m_mouseCollideWithPlayButton;
	bool m_mouseCollideWithExitButton;
	bool m_mouseCollideWithMenuButton;
	bool m_mouseCollideWithRetryButton;

	Vector2f m_HealthBarOriginalPos;
	Vector2f m_HealthBarOriginalScale;

	Vector2f m_ShieldBarOriginalPos;
	Vector2f m_ShieldBarOriginalScale;

	SDL_Color m_White = { 255, 255, 255 };
	SDL_Color m_Black = { 0, 0, 0 };

	SDL_Renderer* m_Renderer;
};
