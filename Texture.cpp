
#include "lib/Texture.h"
#include "lib/UIManager.h"

Texture::Texture()
{
	isCursorCollideWithEnemy = false;
}

Texture& Texture::GetInstance()
{
	static Texture* instance = new Texture;

	return *instance;
}

void Texture::LoadTextures(RenderWindow window)
{
	playerShip = window.loadTexture("res/GFX/PlayerShip.png");
	projectile01 = window.loadTexture("res/GFX/Projectile01.png");

	smallEnemyShips[0] = window.loadTexture("res/GFX/SmallEnemyShip_1.png");
	smallEnemyShips[1] = window.loadTexture("res/GFX/SmallEnemyShip_2.png");
	smallEnemyShips[2] = window.loadTexture("res/GFX/SmallEnemyShip_3.png");

	mediumEnemyShips[0] = window.loadTexture("res/GFX/MediumEnemyShip_1.png");
	mediumEnemyShips[1] = window.loadTexture("res/GFX/MediumEnemyShip_2.png");
	mediumEnemyShips[2] = window.loadTexture("res/GFX/MediumEnemyShip_3.png");

	bigEnemyShips[0] = window.loadTexture("res/GFX/BigEnemyShip_1.png");
	bigEnemyShips[1] = window.loadTexture("res/GFX/BigEnemyShip_2.png");
	bigEnemyShips[2] = window.loadTexture("res/GFX/BigEnemyShip_3.png");

	hitMark[0] = window.loadTexture("res/GFX/HitMark_1.png");
	hitMark[1] = window.loadTexture("res/GFX/HitMark_2.png");
	hitMark[2] = window.loadTexture("res/GFX/HitMark_3.png");

	missile = window.loadTexture("res/GFX/Missile.png");
	blastEffect = window.loadTexture("res/GFX/BlastEffect.png");
	smokeEffect = window.loadTexture("res/GFX/SmokeEffect.png");

	flare = window.loadTexture("res/GFX/Flare.png");

	firstAid = window.loadTexture("res/GFX/FirstAid.png");
	shield = window.loadTexture("res/GFX/Shield.png");

	cursorWhite = window.loadTexture("res/GFX/Cursor_White.png");
	cursorRed = window.loadTexture("res/GFX/Cursor_Red.png");

	button = window.loadTexture("res/GFX/UI/Button.png");
	buttonPressed = window.loadTexture("res/GFX/UI/ButtonPressed.png");

	square = window.loadTexture("res/GFX/UI/Square.png");

	font16 = TTF_OpenFont("res/Fonts/RifficFree-Bold.ttf", 16);
	font28 = TTF_OpenFont("res/Fonts/RifficFree-Bold.ttf", 26);
	font40 = TTF_OpenFont("res/Fonts/RifficFree-Bold.ttf", 40);
	font40_Outline = TTF_OpenFont("res/Fonts/RifficFree-Bold.ttf", 40);
	font50 = TTF_OpenFont("res/Fonts/RifficFree-Bold.ttf", 50);
	font50_Outline = TTF_OpenFont("res/Fonts/RifficFree-Bold.ttf", 50);
	TTF_SetFontOutline(font50_Outline, 3);
	TTF_SetFontOutline(font40_Outline, 3);

	SetEntity();
}

void Texture::SetEntity()
{
	m_PlayerShip = Player(Vector2f(360, 650), playerShip, Vector2f(2.25, 2.25));

	m_CursorWhite = Entity(Vector2f(0, 0), cursorWhite, Vector2f(2, 2));
	m_CursorRed = Entity(Vector2f(0, 0), cursorRed, Vector2f(2, 2));

	m_HealthBar = Entity(Vector2f(0, 0), square, Vector2f(1, 1));
	m_ShieldBar = Entity(Vector2f(0, 0), square, Vector2f(1, 1));
	m_MissileIcon = Entity(Vector2f(0, 0), missile, Vector2f(2, 2));
	m_FlareIcon = Entity(Vector2f(0, 0), flare, Vector2f(2, 2));

	m_PlayButton = Entity(Vector2f(0, 0), button, Vector2f(3, 3));
	m_PlayButtonPressed = Entity(Vector2f(0, 0), buttonPressed, Vector2f(3, 3));

	m_ExitButton = Entity(Vector2f(0, 0), button, Vector2f(3, 3));
	m_ExitButtonPressed = Entity(Vector2f(0, 0), buttonPressed, Vector2f(3, 3));

	m_MenuButton = Entity(Vector2f(0, 0), button, Vector2f(3, 3));
	m_MenuButtonPressed = Entity(Vector2f(0, 0), buttonPressed, Vector2f(3, 3));

	m_RetryButton = Entity(Vector2f(0, 0), button, Vector2f(3, 3));
	m_RetryButtonPressed = Entity(Vector2f(0, 0), buttonPressed, Vector2f(3, 3));
}

void Texture::Update()
{
	m_PlayerShip.Update();
	m_CursorWhite.Update();
	m_CursorRed.Update();
	m_HealthBar.Update();
	m_ShieldBar.Update();

	m_PlayButton.Update();
	m_PlayButtonPressed.Update();

	m_ExitButton.Update();
	m_ExitButtonPressed.Update();

	m_MenuButton.Update();
	m_MenuButtonPressed.Update();

	m_RetryButton.Update();
	m_RetryButtonPressed.Update();
}

void Texture::Render(RenderWindow window)
{
	if (UIManager::GetInstance().m_gameState == UIManager::GetInstance().Playing)
	{
		if (!m_PlayerShip.IsDestroy())
			window.Render(m_PlayerShip, 0, false);
	}

}

