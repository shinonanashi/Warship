
#include "lib/Projectile.h"

Projectile::Projectile(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 3;
}

void Projectile::Update(int dir)
{
	if (IsDestroy())
		return;

	Entity::Update();

	SetPos(Vector2f(GetPos().x, GetPos().y +  (dir * m_Speed)));
}
