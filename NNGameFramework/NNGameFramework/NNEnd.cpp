#include "NNEnd.h"
#include "NNSprite.h"
#include "PRE_DEFINE.h"
#include "NNMainMenu.h"
#include "NNSceneDirector.h"
#include "NNAudioSystem.h"
#include "NNResourceManager.h"
#include "NNLabel.h"


NNEnd::NNEnd(void)
{
	m_pClear	=	NNLabel::Create( L"GAME OVER", L"batmanforeveralternate", 100.f, 0x000000 );
	m_pClear->SetPosition( 30, 50 );

	m_pBackground	= NNSprite::Create( END_SPRITE2 );
	m_pBackground->SetImageHeight( GAME_HEIGHT );
	m_pBackground->SetImageWidth( GAME_WIDTH );
	m_pBackground->SetZindex( 0 );
	m_pBackground->SetOpacity( 0.5f );
	
	m_SumTime = 0.f;
	AddChild( m_pBackground );
	AddChild( m_pClear );
	
}

NNEnd::NNEnd(int point, int combo, int tot_combo )
{
	m_pCombo	=	NNLabel::Create( L"", L"batmanforeveralternate", 50.f, 0x000000 );
	swprintf_s( m_Combo, _countof( m_Combo ), L"%d MAX COMBO ", combo );
	m_pCombo->SetString( m_Combo );
	m_pCombo->SetPosition( 100, 300 );
	
	m_pPoint	=	NNLabel::Create( L"", L"batmanforeveralternate", 50.f, 0x000000 );
	swprintf_s( m_Point, _countof( m_Point ), L"%d POINT", point );
	m_pPoint->SetString( m_Point );
	m_pPoint->SetPosition( 100, 400 );

	m_pTotCombo	=	NNLabel::Create( L"", L"batmanforeveralternate", 50.f, 0x000000 );
	swprintf_s( m_TotCombo, _countof( m_TotCombo ), L"%d TOTAL COMBO", tot_combo );
	m_pTotCombo->SetString( m_TotCombo );
	m_pTotCombo->SetPosition( 100, 500 );

	m_pClear	=	NNLabel::Create( L"GAME CLEAR", L"batmanforeveralternate", 100.f, 0x000000 );
	m_pClear->SetPosition( 20, 50 );

	m_pBackground	= NNSprite::Create( END_SPRITE );
	m_pBackground->SetImageHeight( GAME_HEIGHT );
	m_pBackground->SetImageWidth( GAME_WIDTH );
	m_pBackground->SetZindex( 0 );
	m_pBackground->SetOpacity( 0.5f );


	m_SumTime = 0.f;

	AddChild( m_pBackground );
	AddChild( m_pPoint );
	AddChild( m_pCombo);
	AddChild( m_pClear );
	AddChild( m_pTotCombo );
}

void NNEnd::Update(float dTime)
{
	NNScene::Update( dTime );

	m_SumTime += dTime;

	if( m_SumTime >= 5.f )
	{
		NNSceneDirector::GetInstance()->ChangeScene( new NNMainMenu() );
	}
}

NNEnd::~NNEnd(void)
{

}
