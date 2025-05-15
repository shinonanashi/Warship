
#include "lib/UIManager.h"
#include "lib/Collision.h"
#include "lib/ObjectSpawner.h"

#include <string>

UIManager::UIManager()
{
	m_Score = 0;
	m_ScoreText = "Score: 0";
	m_HealthBarOriginalPos = Vector2f(90, 700);
	m_HealthBarOriginalScale = Vector2f(4, 0.5);

	m_ShieldBarOriginalPos = Vector2f(90, 687);
	m_ShieldBarOriginalScale = Vector2f(4, 0.1);

	PositionAndScalingUI();

	m_gameState = Menu;

	m_Exit = false;
	m_mouseButtonDown = false;
}

UIManager& UIManager::GetInstance()
{
	static UIManager* instance = new UIManager;

	return *instance;
}

void UIManager::Update()
{
	if (!Texture::GetInstance().m_PlayerShip.missileCoolDown)
		m_MissileText = "x 1";
	else
		m_MissileText = "x 0";

	if (!Texture::GetInstance().m_PlayerShip.flareCoolDown)
		m_FlareText = "x 1";
	else
		m_FlareText = "x 0";

	CheckUICollision();

}

void UIManager::HandleEvent(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
		m_mouseButtonDown = true;
	else if (event.type == SDL_MOUSEBUTTONUP)
		m_mouseButtonDown = false;

	if (event.type == SDL_MOUSEBUTTONUP && m_mouseCollideWithPlayButton && m_gameState == Menu)
	{
		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Button);
		m_gameState = Playing;
	}

	if (event.type == SDL_MOUSEBUTTONUP && m_mouseCollideWithExitButton && m_gameState == Menu)
	{
		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Button);
		m_Exit = true;
	}

	if (event.type == SDL_MOUSEBUTTONUP && m_mouseCollideWithMenuButton && m_gameState == GameOver)
	{
		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Button);
		m_gameState = Menu;
		Reset();
	}

	if (event.type == SDL_MOUSEBUTTONUP && m_mouseCollideWithRetryButton && m_gameState == GameOver)
	{
		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Button);
		m_gameState = Playing;
		Reset();
	}
}

void UIManager::CheckUICollision()
{
	if (Collision::IsCollide(&Texture::GetInstance().m_PlayButton.GetDst(), &Texture::GetInstance().m_CursorWhite.GetDst()))
		m_mouseCollideWithPlayButton = true;
	else
		m_mouseCollideWithPlayButton = false;

	if (Collision::IsCollide(&Texture::GetInstance().m_ExitButton.GetDst(), &Texture::GetInstance().m_CursorWhite.GetDst()))
		m_mouseCollideWithExitButton = true;
	else
		m_mouseCollideWithExitButton = false;

	if (Collision::IsCollide(&Texture::GetInstance().m_MenuButton.GetDst(), &Texture::GetInstance().m_CursorWhite.GetDst()))
		m_mouseCollideWithMenuButton = true;
	else
		m_mouseCollideWithMenuButton = false;

	if (Collision::IsCollide(&Texture::GetInstance().m_RetryButton.GetDst(), &Texture::GetInstance().m_CursorWhite.GetDst()))
		m_mouseCollideWithRetryButton = true;
	else
		m_mouseCollideWithRetryButton = false;
}

void UIManager::PositionAndScalingUI()
{
	Texture::GetInstance().m_HealthBar.SetPos(m_HealthBarOriginalPos);
	Texture::GetInstance().m_HealthBar.SetScale(m_HealthBarOriginalScale);

	Texture::GetInstance().m_ShieldBar.SetPos(m_ShieldBarOriginalPos);
	Texture::GetInstance().m_ShieldBar.SetScale(Vector2f(0, 0.1));

	Texture::GetInstance().m_MissileIcon.SetPos(Vector2f(40, 669));

	Texture::GetInstance().m_FlareIcon.SetPos(Vector2f(40, 634));

	Texture::GetInstance().m_PlayButton.SetPos(Vector2f(350, 320));
	Texture::GetInstance().m_PlayButtonPressed.SetPos(Vector2f(350, 320));

	Texture::GetInstance().m_ExitButton.SetPos(Vector2f(350, 390));
	Texture::GetInstance().m_ExitButtonPressed.SetPos(Vector2f(350, 390));

	Texture::GetInstance().m_MenuButton.SetPos(Vector2f(350, 320));
	Texture::GetInstance().m_MenuButtonPressed.SetPos(Vector2f(350, 320));

	Texture::GetInstance().m_RetryButton.SetPos(Vector2f(350, 390));
	Texture::GetInstance().m_RetryButtonPressed.SetPos(Vector2f(350, 390));

}

void UIManager::UpdateHealthBar(int damage)
{
	int hitpoints = Texture::GetInstance().m_PlayerShip.GetHitPoints();

	float scale = ((((float)hitpoints / 50.0)));


	Texture::GetInstance().m_HealthBar.SetScale(Vector2f(scale * 4.0, 0.5));
	Texture::GetInstance().m_HealthBar.SetPos(Vector2f(Texture::GetInstance().m_HealthBar.GetPos().x - 1.222 * damage, 700));
}

void UIManager::UpdateShieldBar(int damage)
{
	int shield = Texture::GetInstance().m_PlayerShip.GetShield();

	float scale = ((((float)shield / 20)));

	Texture::GetInstance().m_ShieldBar.SetScale(Vector2f(scale * 4.0, 0.1));
	Texture::GetInstance().m_ShieldBar.SetPos(Vector2f(Texture::GetInstance().m_ShieldBar.GetPos().x - 3.2 * damage, 687));
}

void UIManager::UpdateScore(int p_Score)
{
	m_Score += p_Score;
	m_ScoreText = "Score: " + std::to_string(m_Score);
}

void UIManager::SetRenderer(SDL_Renderer* renderer)
{
	m_Renderer = renderer;
}

void UIManager::SetKills(int p_Kills)
{
	m_Kills += p_Kills;
}

void UIManager::ResetHealthBar()
{
	Texture::GetInstance().m_HealthBar.SetPos(m_HealthBarOriginalPos);
	Texture::GetInstance().m_HealthBar.SetScale(m_HealthBarOriginalScale);
}

void UIManager::ResetShieldBar()
{
	Texture::GetInstance().m_ShieldBar.SetPos(m_ShieldBarOriginalPos);
	Texture::GetInstance().m_ShieldBar.SetScale(m_ShieldBarOriginalScale);
}

void UIManager::Reset()
{
	Texture::GetInstance().m_PlayerShip.SetDestroyFalse();
	Texture::GetInstance().m_PlayerShip.SetHitPoints(50);
	Texture::GetInstance().m_PlayerShip.SetShield(0);
	Texture::GetInstance().m_PlayerShip.GetFlares().clear();

	ResetHealthBar();

	Texture::GetInstance().m_ShieldBar.SetPos(m_ShieldBarOriginalPos);
	Texture::GetInstance().m_ShieldBar.SetScale(Vector2f(0, 0.1));

	Texture::GetInstance().m_PlayerShip.SetPos(Vector2f(360, 650));

	ObjectSpawner::GetInstance().GetSmallEnemies().clear();

	ObjectSpawner::GetInstance().GetMediumEnemies().clear();

	ObjectSpawner::GetInstance().GetBigEnemies().clear();

	ObjectSpawner::GetInstance().GetFirstAid().SetPos(Vector2f(-10, -10));
	ObjectSpawner::GetInstance().GetShield().SetPos(Vector2f(-10, -10));

	m_Score = 0;
	m_ScoreText = "Score: 0";
}

void UIManager::Render(RenderWindow& window)
{
	if (m_gameState == Menu)
	{
		window.RenderText(Vector2f(350, 147), "War Ship", Texture::GetInstance().font50_Outline, m_Black);
		window.RenderText(Vector2f(350, 150), "War Ship", Texture::GetInstance().font50, m_White);

		if (m_mouseButtonDown && m_mouseCollideWithPlayButton)
		{
			window.Render(Texture::GetInstance().m_PlayButtonPressed, 0, false);
			window.RenderText(Vector2f(350, 323), "Play", Texture::GetInstance().font28, m_White);
		}
		else
		{
			window.Render(Texture::GetInstance().m_PlayButton, 0, false);
			window.RenderText(Vector2f(350, 316), "Play", Texture::GetInstance().font28, m_White);
		}

		if (m_mouseButtonDown && m_mouseCollideWithExitButton)
		{
			window.Render(Texture::GetInstance().m_ExitButtonPressed, 0, false);
			window.RenderText(Vector2f(350, 393), "Exit", Texture::GetInstance().font28, m_White);
		}
		else
		{
			window.Render(Texture::GetInstance().m_ExitButton, 0, false);
			window.RenderText(Vector2f(350, 388), "Exit", Texture::GetInstance().font28, m_White);
		}
	}
	else if (m_gameState == Playing)
	{
		window.Render(Texture::GetInstance().m_HealthBar, 0, false);

		window.Render(Texture::GetInstance().m_ShieldBar, 0, false);

		window.Render(Texture::GetInstance().m_MissileIcon, 0, false);
		window.Render(Texture::GetInstance().m_FlareIcon, 0, false);

		//Texts
		window.RenderText(Vector2f(67, 669), m_MissileText, Texture::GetInstance().font16, m_White);
		window.RenderText(Vector2f(67, 634), m_FlareText, Texture::GetInstance().font16, m_White);
		window.RenderText(Vector2f(630, 680), m_ScoreText, Texture::GetInstance().font28, m_White);
	}
	else
	{
		if (m_mouseButtonDown && m_mouseCollideWithMenuButton)
		{
			window.Render(Texture::GetInstance().m_MenuButtonPressed, 0, false);
			window.RenderText(Vector2f(350, 323), "Menu", Texture::GetInstance().font28, m_White);
		}
		else
		{
			window.Render(Texture::GetInstance().m_MenuButton, 0, false);
			window.RenderText(Vector2f(350, 316), "Menu", Texture::GetInstance().font28, m_White);
		}

		if (m_mouseButtonDown && m_mouseCollideWithRetryButton)
		{
			window.Render(Texture::GetInstance().m_RetryButtonPressed, 0, false);
			window.RenderText(Vector2f(350, 393), "Retry", Texture::GetInstance().font28, m_White);
		}
		else
		{
			window.Render(Texture::GetInstance().m_RetryButton, 0, false);
			window.RenderText(Vector2f(350, 388), "Retry", Texture::GetInstance().font28, m_White);
		}

		window.RenderText(Vector2f(350, 147), "Game Over", Texture::GetInstance().font50_Outline, m_Black);
		window.RenderText(Vector2f(350, 150), "Game Over", Texture::GetInstance().font50, m_White);
		window.RenderText(Vector2f(350, 222), m_ScoreText, Texture::GetInstance().font40_Outline, m_Black);
		window.RenderText(Vector2f(350, 225), m_ScoreText, Texture::GetInstance().font40, m_White);
	}

}

