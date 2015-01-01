#include "NNMineZombie.h"
#include "NNAnimation.h"
#include "PRE_DEFINE.h"


NNMineZombie::NNMineZombie(void)
{
	ZombieAnimationInit();
	AddChild( m_pMine_Zombie );
}


NNMineZombie::~NNMineZombie(void)
{
}

void NNMineZombie::ZombieAnimationInit()
{
	m_pMine_Zombie = NNAnimation::Create( 18, 0.08f, MINE_ZOMBIE_SPRITE_0, MINE_ZOMBIE_SPRITE_1,
		MINE_ZOMBIE_SPRITE_2, MINE_ZOMBIE_SPRITE_3, MINE_ZOMBIE_SPRITE_4 );
}