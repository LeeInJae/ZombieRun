#include "NNBulletManager.h"
#include "NNDefaultBullet.h"
#include "PRE_DEFINE.h"
#include "NNZombie.h"
#include "NNEffectManager.h"
#include "NNResourceManager.h"
#include "NNAudioSystem.h"
#include "NNSoundManager.h"

NNBulletManager* NNBulletManager::m_pInstance = nullptr;

NNBulletManager::NNBulletManager(void)
{
}


NNBulletManager::~NNBulletManager(void)
{
}

NNBulletManager* NNBulletManager::GetInstance()
{
	if( m_pInstance == nullptr )
	{
		m_pInstance = new NNBulletManager;
	}
	return m_pInstance;
}

void NNBulletManager::ReleaseInstance()
{
	if( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void NNBulletManager::Update(float dTime)
{
	NNObject::Update( dTime );
	RemoveBulletCheck();
}

void NNBulletManager::MakeBullet( BULLET_KIND kind )
{
	switch( kind )
	{
	case DEFAULT:
		NNDefaultBullet* Bullet1;
		Bullet1= new NNDefaultBullet;
		Bullet1->SetPosition( 500, 330 );
		Bullet1->SetZindex( 5 );
		Bullet1->SetScale( 1.0f, 1.0f );
		m_BulletList.push_back( Bullet1 );
		AddChild( Bullet1 );
		break;

	default:
		break;
	}
}

//
void NNBulletManager::RemoveBulletCheck()
{
	//range base for로 하면 이미 담겨져 있는 애를 가리켜 줌.
	for( auto Bullet_Iter = m_BulletList.begin(); Bullet_Iter != m_BulletList.end(); )
	{
		if( (*Bullet_Iter)->CheckLifeTime() )
		{
			auto pBullet = *Bullet_Iter;
			Bullet_Iter = m_BulletList.erase( Bullet_Iter );
			RemoveChild( pBullet, true );
		}
		else
		{
			++Bullet_Iter;
		}
	}
}

void NNBulletManager::Zombie_Bullet_HitCheck( NNZombie* pZombie)
{
	HIT_RECT bullet, zombie;

	int damage = 1;
	zombie.left = pZombie->GetPositionX();
	zombie.right = zombie.left + ZOMBIE_WIDTH;
	zombie.up = pZombie->GetPositionY();
	zombie.down = zombie.up + ZOMBIE_HEIGHT;

	for( auto Bullet_Iter = m_BulletList.begin(); Bullet_Iter != m_BulletList.end(); )
	{
		auto pBullet = *Bullet_Iter;
		bullet.left = pBullet->GetPositionX();
		bullet.right = bullet.left + DEFAULT_BULLET_WIDTH;
		bullet.up = pBullet->GetPositionY();
		bullet.down = bullet.up + DEFAULT_BULLET_HEIGHT;

		if( !zombie.HitCheck( bullet ) )
		{
			++Bullet_Iter;
			continue;
		} 
		else
		{
			NNSoundManager::GetInstance()->Play(NNSoundManager::GetInstance()->SE_Sound[ EXPLODE ]);
			NNEffectManager::GetInstance()->MakeEffect( CRASH, pBullet->GetPositionX(),  pBullet->GetPositionY() );
			pZombie->SetLife( pZombie->GetLife() - damage );
			Bullet_Iter = m_BulletList.erase( Bullet_Iter );
			RemoveChild( pBullet, true );
			if( pZombie->GetPositionX()-DEFAULT_BULLET_DAMAGE > LIMIT_ZOMBIE_LEFT_PSITION_X )
				pZombie->SetPosition( pZombie->GetPositionX()-DEFAULT_BULLET_DAMAGE , pZombie->GetPositionY() );
		}
	}
}