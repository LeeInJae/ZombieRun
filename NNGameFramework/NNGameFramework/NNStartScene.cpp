#include "NNStartScene.h"
#include "NNSprite.h"
#include "PRE_DEFINE.h"
#include "NNObject.h"
#include "NNLabel.h"
#include "NNApplication.h"
#include "NNAnimation.h"
#include "NNPlayerCharacter.h"
#include "NNZombie.h"
#include "NNInputEng.h"
#include "NNMapManager.h"
#include "NNInputSystem.h"
#include <iostream>
#include "NNEnd.h"
#include "NNResourceManager.h"
#include "NNAudioSystem.h"
#include "NNPlain.h"
#include "NNEffectManager.h"
#include "NNBulletManager.h"
#include "NNSoundManager.h"

NNStartScene::NNStartScene(void)
{
	Class_Init();
	UI_Init();
	Number_Init();
	Position_Init();

	AddChild( m_pZombie );
	AddChild( m_pCharacter );
	AddChild( m_pReadyTime );
	AddChild( m_pInputEng );
	AddChild( m_ElapsedPlayTimeLabel );
	AddChild( m_pPointLabel );
	AddChild( m_pComboLabel );
	AddChild( m_pPlain );
	NNMapManager::GetInstance();
	NNEffectManager::GetInstance();
	NNBulletManager::GetInstance();

	if( !NNSoundManager::GetInstance()->m_ZombieChannel )
	{
		NNSoundManager::GetInstance()->PlayAndGetChannel(
		NNSoundManager::GetInstance()->SE_Sound[ ZOMBIE ],
		&NNSoundManager::GetInstance()->m_ZombieChannel );
	
	}
	NNSoundManager::GetInstance()->Pause(NNSoundManager::GetInstance()->m_ZombieChannel );
	NNSoundManager::GetInstance()->Pause( NNSoundManager::GetInstance()->m_ZombieDieChannel );
}

NNStartScene::~NNStartScene(void)
{
	NNMapManager::ReleaseInstance();
	NNEffectManager::ReleaseInstance();
	NNBulletManager::ReleaseInstance();
}

void NNStartScene::Class_Init()
{
	m_pZombie = new NNZombie();
	m_pCharacter = new NNPlayerCharacter();
	m_pInputEng	= new NNInputEng();
	m_pPlain	= new NNPlain();
}

void NNStartScene::UI_Init()
{
	m_pReadyTime = NNLabel::Create( L"", L"batmanforeveralternate", 50.f, 0x000000 );
	m_pReadyTime->SetPosition( READY_TIME_POSITION_X, READY_TIME_POSITION_Y );
	m_pReadyTime->SetScale( 1.5f, 1.5f );
	m_pReadyTime->SetZindex(1);

	m_ElapsedPlayTimeLabel = NNLabel::Create(L"", L"batmanforeveralternate", 50.f, 0x000000);
	m_ElapsedPlayTimeLabel->SetPosition( ( GAME_WIDTH >> 1 ) - 50.f , 15.f );
	m_ElapsedPlayTimeLabel->SetZindex(0);

	m_pPointLabel = NNLabel::Create(L"", L"batmanforeveralternate", 50.f, 0x000000 );
	m_pPointLabel->SetPosition( 15.f , 15.f );
	m_pPointLabel->SetZindex(0);

	m_pComboLabel = NNLabel::Create( L"", L"batmanforeveralternate", 30.f, 0x000000 );
	m_pComboLabel->SetPosition( 580.f, 23.f );
	m_pComboLabel->SetZindex(0);
}

void NNStartScene::Number_Init()
{
	m_Point = 0;
	m_EndSoundCheck = false;
	m_SumTime = 0; //dTime을 더하는 변수
	m_CheckTime = false;
	m_TimePositionCheck = 1;
	m_LevelTime = 0.f;
	m_CorrectCount = 0;
	//m_End	=	false;
}


void NNStartScene::Position_Init()
{
	m_pZombie->SetPosition( START_ZOMBIE_POSITION_X, START_ZOMBIE_POSITION_Y );
	m_pZombie->SetZindex( 1 );
	m_pZombie->SetScale( 2.0, 2.0 );
	m_pZombie->SetVisible( false );

	m_pCharacter->SetPosition( START_CHARACTER_POSITION_X, START_CHARACTER_POSITION_Y );
	m_pCharacter->SetZindex( 1 );
	m_pCharacter->SetScale( 1.2, 1.2 );
	m_pCharacter->SetVisible( false );

	m_pPlain->SetPosition( PLAIN_POSITION_X, PLAIN_POSITION_Y );
	m_pPlain->SetZindex( 1 );
	m_pPlain->SetScale( 1.8, 1.8 );
	m_pPlain->SetVisible( false );
}


void NNStartScene::Update(float dTime)
{
	NNScene::Update( dTime );
	
	if( !m_CheckTime )
	{
		m_SumTime += dTime;
	
		if( static_cast<int>( m_SumTime ) <= 3 )
		{
			swprintf_s( m_ReadyTime, _countof( m_ReadyTime ), L"%d", 3 - static_cast<int>(m_SumTime) );
			m_pReadyTime->SetString( m_ReadyTime );
		}
		else
		{
			m_CheckTime = true;
			RemoveChild( m_pReadyTime, true );
			m_pZombie->SetVisible( true );
			m_pCharacter->SetVisible( true );
			m_pPlain->SetVisible( true );
			m_SumTime = 0.f;
		}

		return;
	}

 	if( !m_pZombie->GetDieCheck() && NNSoundManager::GetInstance()->IsPaused( NNSoundManager::GetInstance()->m_ZombieChannel) )
 		NNSoundManager::GetInstance()->Resume( NNSoundManager::GetInstance()->m_ZombieChannel );
	
	m_SumTime += dTime;
	m_LevelTime += dTime; //난이도 조절하는 시간( 따라잡히는 속도 업)
	m_Point += dTime;

	NNMapManager::GetInstance()->Update( dTime );
	NNEffectManager::GetInstance()->Update( dTime );
	NNBulletManager::GetInstance()->Update( dTime );
	NNBulletManager::GetInstance()->Zombie_Bullet_HitCheck( m_pZombie );

	if( m_pZombie->GetDieCheck() )
	{
		if( !m_pInputEng->GetEnd() )
		{
			m_pInputEng->SetEnd( true );
		}

		if( m_pZombie->IsPlayAnimation() )
		{
			NNSoundManager::GetInstance()->Pause( NNSoundManager::GetInstance()->m_ZombieDieChannel );
			NNSceneDirector::GetInstance()->ChangeScene( new NNEnd( m_Point, m_pInputEng->GetMaxCombo(), m_pInputEng->GetMaxTotCombo()  ) );
			return;
		}
		return;
	}

	float character_PositionX; 
	float character_PositionY;

	character_PositionX = m_pCharacter->GetPositionX();
	character_PositionY= m_pCharacter->GetPositionY();

	if( character_PositionX - m_pCharacter->GetBackSpeed() > LIMIT_CHARHACTER_LEFT_POSITION_X )
		m_pCharacter->SetPosition( character_PositionX - m_pCharacter->GetBackSpeed(), character_PositionY );
	
	if( m_pZombie->GetPositionX() + ZOMBIE_PURSUE_SPEED < LIMIT_ZOMBIE_RIGHT_PSITION_X )
		m_pZombie->SetPosition( m_pZombie->GetPositionX() + ZOMBIE_PURSUE_SPEED , m_pZombie->GetPositionY() );

//	if( m_CorrectCount <= m_pZombie->GetLife() )
	{
		if( NNInputSystem::GetInstance()->IsDownAnyKey() == true && m_pInputEng->GetCheckAnswer() == true ) //정답을 맞췄으면
		{
			++m_CorrectCount;
			NNEffectManager::GetInstance()->MakeEffect( PLAIN, 0, 0 );
			NNBulletManager::GetInstance()->MakeBullet( DEFAULT );
			//NNAudioSystem::GetInstance()->Stop( m_ZombieSound );

//			NNAudioSystem::GetInstance()->Play( m_AnswerSound );
			NNSoundManager::GetInstance()->Play( NNSoundManager::GetInstance()->SE_Sound[ ANSWER ] );
			m_Point += m_pInputEng->GetCombo();
			if( character_PositionX + m_pCharacter->GetFrontSpeed() < LIMIT_CHARHACTER_RIGHT_POSITION_X )
				m_pCharacter->SetPosition( character_PositionX + m_pCharacter->GetFrontSpeed(), character_PositionY );
		}
		else if( NNInputSystem::GetInstance()->IsDownAnyKey() == true && m_pInputEng->GetCheckAnswer() == false )
		{
		//	NNAudioSystem::GetInstance()->Play( m_WrongSound );
			NNSoundManager::GetInstance()->Play( NNSoundManager::GetInstance()->SE_Sound[ WRONG ] );
			if( m_pZombie->GetPositionX() + ZOMBIE_SPEED < LIMIT_ZOMBIE_RIGHT_PSITION_X )
				m_pZombie->SetPosition( m_pZombie->GetPositionX() + ZOMBIE_SPEED , m_pZombie->GetPositionY() );
		}
	}
	/*
	if( m_LevelTime >= LEVEL_TIME )
	{
		m_pCharacter->SetBackSpeed( m_pCharacter->GetBackSpeed() + LEVEL_SPEED );
		//m_pInputEng->SetSpeed( m_pInputEng->GetSpeed() + TYPGIN_UP_SPEED );
		m_LevelTime = 0.f;
	}
	*/
	HIT_RECT character, zombie;

	character.left = m_pCharacter->GetPositionX();
	character.right = character.left + CHARACTER_WIDTH;
	character.up = m_pCharacter->GetPositionY();
	character.down = character.up + CHARACTER_HEIGHT;

	zombie.left = m_pZombie->GetPositionX();
	zombie.right = zombie.left + ZOMBIE_WIDTH;
	zombie.up = m_pZombie->GetPositionY();
	zombie.down = zombie.up + ZOMBIE_HEIGHT;

	if( character.HitCheck( zombie ) )//충돌체크
	{
		NNSoundManager::GetInstance()->Pause( NNSoundManager::GetInstance()->m_ZombieChannel );
 		NNSceneDirector::GetInstance()->ChangeScene( new NNEnd() );
		return;
	}

	//위치조정
	/*
	if( ( m_TimePositionCheck * 10 ) <= m_SumTime )
	{
		float px = m_ElapsedPlayTimeLabel->GetPositionX();
		float py = m_ElapsedPlayTimeLabel->GetPositionY();
		m_ElapsedPlayTimeLabel->SetPosition( px - ( TIME_FONT_SCALE / 4 ), py );
		m_TimePositionCheck *= 10;
	}
	*/

	swprintf_s( m_PlayTimeString, _countof( m_PlayTimeString ), L"%0.f M", m_SumTime );
	m_ElapsedPlayTimeLabel->SetString( m_PlayTimeString );
	
	swprintf_s( m_PointString, _countof( m_PointString ), L"%0.f", m_Point );
	m_pPointLabel->SetString( m_PointString );

	swprintf_s( m_ComboString, _countof( m_ComboString ), L"%d combo", m_pInputEng->GetCombo() );
	m_pComboLabel->SetString( m_ComboString );
}

void NNStartScene::Render()
{
	NNMapManager::GetInstance()->Render();
	NNEffectManager::GetInstance()->Render();
	NNScene::Render();
	NNBulletManager::GetInstance()->Render();
}