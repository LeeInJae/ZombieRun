#include "NNPlainEffect.h"
#include "NNAnimation.h"
#include "PRE_DEFINE.h"


NNPlainEffect::NNPlainEffect(void)
{
	m_LifeTime = 0.07 * 2;
	m_ElapsedTime = 0.f;
	m_Effect = NNAnimation::Create( 2, PLAIN_EFFECT_SPRITE_0, PLAIN_EFFECT_SPRITE_1 );
	m_Effect->SetFrameTime( 0.07f );
	m_Effect->SetZindex( 3 );
	AddChild( m_Effect );
}


NNPlainEffect::~NNPlainEffect(void)
{
}

