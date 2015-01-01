#include "NNCrashEffect.h"
#include "NNAnimation.h"
#include "PRE_DEFINE.h"


NNCrashEffect::NNCrashEffect(void)
{
	m_LifeTime = 0.05 * 8;
	m_ElapsedTime = 0.f;
	m_Effect = NNAnimation::Create( 8, CRASH_EFFECT_SPRITE_0, CRASH_EFFECT_SPRITE_1, CRASH_EFFECT_SPRITE_2,
		CRASH_EFFECT_SPRITE_3, CRASH_EFFECT_SPRITE_4, CRASH_EFFECT_SPRITE_5,
		CRASH_EFFECT_SPRITE_6, CRASH_EFFECT_SPRITE_7 );
	m_Effect->SetFrameTime( 0.05f );

	m_Effect->SetZindex( 3 );
	AddChild( m_Effect );
}


NNCrashEffect::~NNCrashEffect(void)
{
}
