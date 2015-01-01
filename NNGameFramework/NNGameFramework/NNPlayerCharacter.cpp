#include "NNPlayerCharacter.h"
#include "NNAnimation.h"
#include "PRE_DEFINE.h"


NNPlayerCharacter::NNPlayerCharacter(void)
{
	m_BackSpeed = 0.1f;
	m_FrontSpeed = 5.0f;
	m_WrongAnswerSpeed = 0.01f;
	CharacterAnimationInit();
	AddChild( m_pCharacter );
}

NNPlayerCharacter::~NNPlayerCharacter(void)
{
}

void NNPlayerCharacter::CharacterAnimationInit()
{
	m_pCharacter = NNAnimation::Create( 8, CHARACTER_RIGHT_SPRITE_0, CHARACTER_RIGHT_SPRITE_1,
		CHARACTER_RIGHT_SPRITE_2, CHARACTER_RIGHT_SPRITE_3,CHARACTER_RIGHT_SPRITE_4, CHARACTER_RIGHT_SPRITE_5,
		CHARACTER_RIGHT_SPRITE_6, CHARACTER_RIGHT_SPRITE_7 );
	m_pCharacter->SetFrameTime( 0.1f );
}