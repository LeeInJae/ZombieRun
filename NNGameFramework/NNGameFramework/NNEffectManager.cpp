#include "NNEffectManager.h"
#include "NNPlainEffect.h"
#include "PRE_DEFINE.h"
#include "NNCrashEffect.h"

NNEffectManager* NNEffectManager::m_pInstance = nullptr;

NNEffectManager::NNEffectManager(void)
{
}


NNEffectManager::~NNEffectManager(void)
{
}

NNEffectManager* NNEffectManager::GetInstance()
{
	if( m_pInstance == nullptr )
	{
		m_pInstance = new NNEffectManager;
	}
	return m_pInstance;
}

void NNEffectManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void NNEffectManager::Update(float dTime)
{
	NNObject::Update( dTime );
	RemoveEffectCheck();
}

void NNEffectManager::RemoveEffectCheck()
{
	// Check Effect Remove, PooBulletHitEffect Remove
	for( auto Effect_Iter = m_EffectList.begin(); Effect_Iter != m_EffectList.end(); )
	{
		if(  (*Effect_Iter)->CheckLifeTime() )
		{
			auto pEffect = *Effect_Iter;

			Effect_Iter = m_EffectList.erase( Effect_Iter );
			RemoveChild( pEffect, true );
		}
		else
		{
			++Effect_Iter;
		}
	}
}

void NNEffectManager::MakeEffect( EFFECT_KIND kind, float position_x, float position_y )
{
	switch( kind )
	{
	case PLAIN:
		NNPlainEffect* Effect1;
		Effect1= new NNPlainEffect;
		Effect1->SetPosition( 648, 330 );
		Effect1->SetZindex( 0 );
		Effect1->SetScale( 1.8f, 1.8f );
		Effect1->SetRotation( -0.4 );
		m_EffectList.push_back( Effect1 );
		AddChild( Effect1);
		break;

	case CRASH:
		NNCrashEffect* Effect2;
		Effect2 = new NNCrashEffect;
		Effect2->SetPosition( position_x, position_y );
		Effect2->SetZindex( 0 );
		Effect2->SetScale( 0.5f, 0.5f );
		Effect2->SetRotation( -0.4 );
		m_EffectList.push_back( Effect2 );
		AddChild( Effect2 );
		break;

	default:
		break;
	}
}
