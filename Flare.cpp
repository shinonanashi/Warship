#include "lib/Flare.h"
#include "lib/AudioManager.h"

Flare::Flare(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int dir, float angle)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 0.75;
	m_Dir = dir;
	m_Angle = angle;

	AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Flares);
}

void Flare::Update()
{
	if (IsDestroy())
		return;

	Entity::Update();

	SetPos(Vector2f(GetPos().x + m_Dir * m_Speed, GetPos().y + 0.25));
}
