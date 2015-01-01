#include "NNStep.h"
#include "NNInputSystem.h"
#include "NNSceneDirector.h"
#include "NNStartScene.h"
#include "NNLabel.h"
#include "NNSprite.h"


NNStep::NNStep(void)
{
	m_Toggle = STEP1; //토글값을 0으로 셋팅, 0= START, 1= EXIT
	m_DelayTime = 0; //키보드입력 딜레이시간 셋팅

	m_pBackground	= NNSprite::Create( STEP_SPRITE );
	m_pBackground->SetImageHeight( GAME_HEIGHT );
	m_pBackground->SetImageWidth( GAME_WIDTH );
	m_pBackground->SetZindex( 0 );

	for( int i=0; i<STEP_COUNT; ++i )
	{
		swprintf_s( m_StepCharacter[ i ], _countof( m_StepCharacter[ i ] ), L"STEP %d", i+1 );
		m_pStep[ i ] = NNLabel::Create( L"", L"Feast of Flesh BB", 45.f,0x000000 );
		m_pStep[ i ]->SetPosition( START_LABEL_POSITION_X, START_LABEL_POSITION_Y - ( 400 - i * 43 ) );
		m_pStep[ i ]->SetZindex( 1 );
		m_pStep[ i ]->SetString( m_StepCharacter[ i ] );
	}
	m_pStep[ 0 ]->SetColor( 0xff, 0x00, 0x00 );

	AddChild( m_pBackground );
	for( int i=0; i<STEP_COUNT; ++i )
	{
		AddChild( m_pStep[ i ] );
	}
}

NNStep::~NNStep(void)
{
}

void NNStep::Update(float dTime)
{
	m_DelayTime += dTime;

	NNScene::Update( dTime );

	int pivot = m_Toggle;

	if( m_DelayTime >= 0.15f )
	{
		if( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_PRESSED ) //아래 화살표가 눌러졌다면 메뉴 밑으로 이동
		{
			pivot = ( m_Toggle + 1 ) % STEP_COUNT;
			m_Toggle = static_cast<STEP>( pivot );

			if( pivot != STEP_COUNT )
			{
				for( int i=0; i<STEP_COUNT; ++i )
				{
					m_pStep[ i ]->SetColor( 0x00, 0x00, 0x00 );
				}
				m_pStep[ pivot ]->SetColor( 0xff, 0x00, 0x00 );	
			}
			m_DelayTime = 0.f;
		}
		else if( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_PRESSED ) //위 화살표가 눌러졌다면 메뉴가 위로 이동
		{
			pivot = m_Toggle - 1;

			if( pivot < 0 )
			{
				pivot = STEP_COUNT - 1;
			}
			m_Toggle = static_cast<STEP>( pivot );

			if( pivot != STEP_COUNT )
			{
				for( int i=0; i<STEP_COUNT; ++i )
				{
					m_pStep[ i ]->SetColor( 0x00, 0x00, 0x00 );
				}
				m_pStep[ pivot ]->SetColor( 0xff, 0x00, 0x00 );	
			}
			m_DelayTime = 0.f;
		}
		else if( NNInputSystem::GetInstance()->GetKeyState( VK_RETURN ) == KEY_PRESSED )
		{
			switch ( m_Toggle )
			{
			case STEP1:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;

			case STEP2:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP3:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP4:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP5:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP6:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP7:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP8:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP9:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP10:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP11:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP12:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;
			case STEP13:
				NNSceneDirector::GetInstance()->ChangeScene( new NNStartScene() );
				return;
				break;

			default:
				break;
			}
		}
	}
}
