#include "NNMainMenu.h"
#include "NNSprite.h"
#include "PRE_DEFINE.h"
#include "NNAnimation.h"
#include "NNLabel.h"
#include "NNInputSystem.h"
#include "NNSceneDirector.h"
#include "NNStartScene.h"
#include "NNStep.h"
#include "NNResourceManager.h"
#include "NNAudioSystem.h"
#include "NNSound.h"
#include "NNSoundManager.h"

NNMainMenu::NNMainMenu(void)
{
	//사운드
	if( !NNSoundManager::GetInstance()->IsPlay( NNSoundManager::GetInstance()->m_BgmChannel ) )
		NNSoundManager::GetInstance()->PlayAndGetChannel(
		NNSoundManager::GetInstance()->SE_Sound[ BGM ],
		&NNSoundManager::GetInstance()->m_BgmChannel );

	//배경 sprite
	m_pBackground	= NNSprite::Create( MAINMENU_SPRITE );
	m_pBackground->SetImageHeight( GAME_HEIGHT );
	m_pBackground->SetImageWidth( GAME_WIDTH );
	m_pBackground->SetZindex( 1 );

	m_pBackboard	= NNSprite::Create( MAINMENU_BACKBOARD_SPRITE );
	m_pBackboard->SetImageHeight( GAME_HEIGHT );
	m_pBackboard->SetImageWidth( GAME_WIDTH );
	m_pBackboard->SetZindex( 0 );
	m_pBackboard->SetOpacity( 0.3f );

	//zombie Animaition
	m_pZombie		= NNAnimation::Create( 18, ZOMBIE_RIGHT_SPRITE_0, ZOMBIE_RIGHT_SPRITE_1,
		ZOMBIE_RIGHT_SPRITE_2, ZOMBIE_RIGHT_SPRITE_3,ZOMBIE_RIGHT_SPRITE_4, ZOMBIE_RIGHT_SPRITE_5,
		ZOMBIE_RIGHT_SPRITE_6, ZOMBIE_RIGHT_SPRITE_7,ZOMBIE_RIGHT_SPRITE_8, ZOMBIE_RIGHT_SPRITE_9,
		ZOMBIE_RIGHT_SPRITE_10, ZOMBIE_RIGHT_SPRITE_11,ZOMBIE_RIGHT_SPRITE_12, ZOMBIE_RIGHT_SPRITE_13,
		ZOMBIE_RIGHT_SPRITE_14, ZOMBIE_RIGHT_SPRITE_15,ZOMBIE_RIGHT_SPRITE_16, ZOMBIE_RIGHT_SPRITE_17);
	m_pZombie->SetFrameTime( 0.1f );
	m_pZombie->SetPosition( MENU_ZOMBIE_POSITION_X, MENU_ZOMBIE_POSITION_Y );
	m_pZombie->SetZindex( 1 );
	m_pZombie->SetScale( 0.8, 0.8 );
	//
	//character Animation
	m_pCharacter = NNAnimation::Create( 8, CHARACTER_RIGHT_SPRITE_0, CHARACTER_RIGHT_SPRITE_1,
		CHARACTER_RIGHT_SPRITE_2, CHARACTER_RIGHT_SPRITE_3,CHARACTER_RIGHT_SPRITE_4, CHARACTER_RIGHT_SPRITE_5,
		CHARACTER_RIGHT_SPRITE_6, CHARACTER_RIGHT_SPRITE_7 );
	m_pCharacter->SetFrameTime( 0.1f );
		
	m_pCharacter->SetPosition( MENU_CHARACTER_POSITION_X, MENU_CHARACTER_POSITION_Y );
	m_pCharacter->SetZindex( 1 );
	m_pCharacter->SetScale( 1.2, 1.2 );
	//
	//Menu Setting
	m_Toggle = START; //토글값을 0으로 셋팅, 0= START, 1= EXIT
	m_DelayTime = 0; //키보드입력 딜레이시간 셋팅

	m_pMenu[ 0 ] = NNLabel::Create( L"S t a r t", L"Feast of Flesh BB", 45.f,0xff0000 );
	m_pMenu[ 0 ]->SetPosition( START_LABEL_POSITION_X, START_LABEL_POSITION_Y );
	m_pMenu[ 0 ]->SetZindex( 1 );

	m_pMenu[ 1 ] = NNLabel::Create( L"OPTION", L"Feast of Flesh BB", 45.f,0x000000 );
	m_pMenu[ 1 ]->SetPosition( EXIT_LABEL_POSITION_X, EXIT_LABEL_POSITION_Y );
	m_pMenu[ 1 ]->SetZindex( 1 );

	m_pMenu[ 2 ] = NNLabel::Create( L"E X I T", L"Feast of Flesh BB", 45.f,0x000000 );
	m_pMenu[ 2 ]->SetPosition( EXIT_LABEL_POSITION_X, EXIT_LABEL_POSITION_Y + 50.f );
	m_pMenu[ 2 ]->SetZindex( 1 );

	AddChild( m_pBackground );
	AddChild( m_pBackboard );
	AddChild( m_pZombie );
	AddChild( m_pCharacter );

	for( int i=0; i<MENU_COUNT; ++i )
	{
		AddChild( m_pMenu[ i ] );
	}
}


NNMainMenu::~NNMainMenu(void)
{
}

void NNMainMenu::Update( float dTime )
{
	NNScene::Update( dTime );
	
	/* 위,아래 메뉴표시하면 , 선택한 메뉴에 빨간색 색칠, 나머지는 흰색 */
	m_DelayTime += dTime;
	
	int pivot = m_Toggle;

	if( m_DelayTime >= 0.15f )
	{
		if( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_PRESSED ) //아래 화살표가 눌러졌다면 메뉴 밑으로 이동
		{
			pivot = ( m_Toggle + 1 ) % MENU_COUNT;
			m_Toggle = static_cast<MENU>( pivot );

			if( pivot != MENU_COUNT )
			{
				for( int i=0; i<MENU_COUNT; ++i )
				{
					m_pMenu[ i ]->SetColor( 0x00, 0x00, 0x00 );
				}
				m_pMenu[ pivot ]->SetColor( 0xff, 0x00, 0x00 );	
			}
			m_DelayTime = 0.f;
		}
		else if( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_PRESSED ) //위 화살표가 눌러졌다면 메뉴가 위로 이동
		{
			pivot = m_Toggle - 1;

			if( pivot < 0 )
			{
				pivot = MENU_COUNT - 1;
			}
			m_Toggle = static_cast<MENU>( pivot );

			if( pivot != MENU_COUNT )
			{
				for( int i=0; i<MENU_COUNT; ++i )
				{
					m_pMenu[ i ]->SetColor( 0x00, 0x00, 0x00 );
				}
				m_pMenu[ pivot ]->SetColor( 0xff, 0x00, 0x00 );	
			}
			m_DelayTime = 0.f;
		}
		else if( NNInputSystem::GetInstance()->GetKeyState( VK_RETURN ) == KEY_PRESSED )
		{
			switch ( m_Toggle )
			{
			case START:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStep() );
				return;
				break;

			default:
				break;
			}
		}
	}
}