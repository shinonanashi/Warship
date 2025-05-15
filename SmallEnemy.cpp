
#include "lib/SmallEnemy.h"

SmallEnemy::SmallEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType)
	:Enemy(p_pos, p_tex, p_scale)
{
	m_Tag = "SmallEnemy";

	DefineShipType(p_shipType);

	m_CurrentFireRate = m_OriginalFireRate;
}

void SmallEnemy::DefineShipType(int type)
{
	switch (type)
	{
		case 1:
			m_shipType = SingleShooter;
			m_BulletOffset = 0;
			m_bulletPair = 1;
			m_Speed = 0.7;
			m_OriginalFireRate = 0.2;
			m_noOfBullets = 3;
			m_ShootDelay = 2;
			hitPoints = 7;
			break;

		case 2:
			m_shipType = DoubleShooter;
			m_BulletOffset = 10;
			m_bulletPair = 2;
			m_Speed = 0.6;
			m_OriginalFireRate = 0.15;
			m_noOfBullets = 2;
			m_ShootDelay = 1.5;
			hitPoints = 5;
			break;

		case 3:
			m_shipType = Faster;
			m_BulletOffset = 10;
			m_bulletPair = 2;
			m_Speed = 0.8;
			m_OriginalFireRate = 0.15;
			m_noOfBullets = 1;
			m_ShootDelay = 2.5;
			hitPoints = 5;
			break;

	default:
		break;
	}
}

