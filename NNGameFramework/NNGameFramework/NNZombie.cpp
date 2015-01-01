#include "NNZombie.h"
#include "NNAnimation.h"
#include "PRE_DEFINE.h"
#include "NNAudioSystem.h"
#include "NNResourceManager.h"
#include "NNSoundManager.h"


NNZombie::NNZombie(void)
{
	m_Life	= 50;
	m_Die	= false;
	ZombieAnimationInit();
	AddChild( m_pZombie );

	//m_DieSound = NNResourceManager::GetInstance()->LoadSoundFromFile("resource/sound/zombie_death.mp3", false );

	if( !NNSoundManager::GetInstance()->m_ZombieDieChannel )
	{
		NNSoundManager::GetInstance()->PlayAndGetChannel(
			NNSoundManager::GetInstance()->SE_Sound[ ZOMBIE_DIE ],
			&NNSoundManager::GetInstance()->m_ZombieDieChannel );
	}
	NNSoundManager::GetInstance()->Pause( NNSoundManager::GetInstance()->m_ZombieDieChannel );
}

NNZombie::~NNZombie(void)
{
}

void NNZombie::ZombieAnimationInit()
{
	m_pZombie = NNAnimation::Create( 18, ZOMBIE_RIGHT_SPRITE_0, ZOMBIE_RIGHT_SPRITE_1,
		ZOMBIE_RIGHT_SPRITE_2, ZOMBIE_RIGHT_SPRITE_3,ZOMBIE_RIGHT_SPRITE_4, ZOMBIE_RIGHT_SPRITE_5,
		ZOMBIE_RIGHT_SPRITE_6, ZOMBIE_RIGHT_SPRITE_7,ZOMBIE_RIGHT_SPRITE_8, ZOMBIE_RIGHT_SPRITE_9,
		ZOMBIE_RIGHT_SPRITE_10, ZOMBIE_RIGHT_SPRITE_11,ZOMBIE_RIGHT_SPRITE_12, ZOMBIE_RIGHT_SPRITE_13,
		ZOMBIE_RIGHT_SPRITE_14, ZOMBIE_RIGHT_SPRITE_15,ZOMBIE_RIGHT_SPRITE_16, ZOMBIE_RIGHT_SPRITE_17);

	m_pZombie_Die = NNAnimation::Create( 24, ZOMBIE_DIE_SPRITE_0, ZOMBIE_DIE_SPRITE_1, ZOMBIE_DIE_SPRITE_2,
		ZOMBIE_DIE_SPRITE_3, ZOMBIE_DIE_SPRITE_4, ZOMBIE_DIE_SPRITE_5, ZOMBIE_DIE_SPRITE_6, ZOMBIE_DIE_SPRITE_7, ZOMBIE_DIE_SPRITE_8,
		ZOMBIE_DIE_SPRITE_9, ZOMBIE_DIE_SPRITE_10, ZOMBIE_DIE_SPRITE_11, ZOMBIE_DIE_SPRITE_12, ZOMBIE_DIE_SPRITE_13, ZOMBIE_DIE_SPRITE_14,
		ZOMBIE_DIE_SPRITE_15, ZOMBIE_DIE_SPRITE_16, ZOMBIE_DIE_SPRITE_17, ZOMBIE_DIE_SPRITE_18, ZOMBIE_DIE_SPRITE_19,
		ZOMBIE_DIE_SPRITE_20, ZOMBIE_DIE_SPRITE_21, ZOMBIE_DIE_SPRITE_22, ZOMBIE_DIE_SPRITE_23);
	m_pZombie_Die->SetLoop( false );

	m_pZombie->SetFrameTime( 0.08f );
	m_pZombie_Die->SetFrameTime( 0.08f );
}

void NNZombie::ChangeAnimaition()
{
	RemoveChild( m_pZombie, false );
	//m_pZombie->SetVisible( false );
	
	m_pZombie_Die->SetScale( 0.9f, 0.9f );
	AddChild( m_pZombie_Die );
}

void NNZombie::Update(float dTime)
{
	NNObject::Update( dTime );
	if( m_Life <= 0 && !m_Die )
	{
		m_Die = true;
		ChangeAnimaition();
		NNSoundManager::GetInstance()->Resume( NNSoundManager::GetInstance()->m_ZombieDieChannel );
		
		if( !NNSoundManager::GetInstance()->IsPaused( NNSoundManager::GetInstance()->m_ZombieChannel ) )
			NNSoundManager::GetInstance()->Pause( NNSoundManager::GetInstance()->m_ZombieChannel );
	}
}

bool NNZombie::IsPlayAnimation()
{
	if( m_pZombie_Die->GetEndAnimation() )
	{
		return true;
	}
	return false;
}
