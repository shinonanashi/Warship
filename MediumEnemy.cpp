
#include "lib/MediumEnemy.h"

MediumEnemy::MediumEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType)
	:Enemy(p_pos, p_tex, p_scale)
{
	m_Tag = "MediumEnemy";

	DefineShipType(p_shipType);

	m_CurrentFireRate = m_OriginalFireRate;
}

void MediumEnemy::DefineShipType(int type)
{
	switch (type)
	{
	case 1:
		m_shipType = DoubleShooter_Slower;
		m_BulletOffset = 12;
		m_bulletPair = 2;
		m_Speed = 0.4;
		m_OriginalFireRate = 0.1;
		m_noOfBullets = 5;
		m_ShootDelay = 3;
		hitPoints = 14;
		break;

	case 2:
		m_shipType = DoubleShooter_Faster;
		m_BulletOffset = 0;
		m_bulletPair = 1;
		m_Speed = 0.5;
		m_OriginalFireRate = 0.15;
		m_noOfBullets = 3;
		m_ShootDelay = 2;
		hitPoints = 10;
		break;

	case 3:
		m_shipType = Faster;
		m_BulletOffset = 12;
		m_bulletPair = 4;
		m_Speed = 0.65;
		m_OriginalFireRate = 0.1;
		m_noOfBullets = 2;
		m_ShootDelay = 2;
		hitPoints = 10;
		break;

	default:
		break;
	}
}

