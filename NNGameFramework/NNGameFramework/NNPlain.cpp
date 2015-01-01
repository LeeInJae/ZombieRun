#include "NNPlain.h"
#include "NNObject.h"
#include "NNAnimation.h"
#include "PRE_DEFINE.h"


NNPlain::NNPlain(void)
{
	PlainAnimationInit();
	m_pPlain->SetZindex( 1 );
	AddChild( m_pPlain );
}


NNPlain::~NNPlain(void)
{
}

void NNPlain::PlainAnimationInit()
{
	m_pPlain = NNAnimation::Create( 6, PLAIN_SPRITE_0, PLAIN_SPRITE_1,
		PLAIN_SPRITE_2, PLAIN_SPRITE_3, PLAIN_SPRITE_4, PLAIN_SPRITE_5 );
	m_pPlain->SetFrameTime( 0.08f );
}