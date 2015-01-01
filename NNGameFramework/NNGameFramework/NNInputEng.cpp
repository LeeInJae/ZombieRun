#include "NNInputEng.h"
#include "NNLabel.h"
#include "PRE_DEFINE.h"
#include <string>
#include "NNInputSystem.h"
#include <iostream>
#include "NNResourceManager.h"
#include "NNAudioSystem.h"
#include "NNEffectManager.h"
#include <string.h>

NNInputEng::NNInputEng(void)
{
	File_Init();
	Number_Init();
	Label_Init();

	AddChild( m_pContentString );
	AddChild( m_pContentString2 );
	m_pContentString->SetVisible( true  );
	m_pContentString2->SetVisible( true );
}

NNInputEng::~NNInputEng(void)
{
	delete m_Wcstring;
	delete m_Wcstring2;
	File_Close();
}

void NNInputEng::Number_Init()
{
	m_End = false;
	m_MaxCombo = 0;
	m_TotCombo = 0;
	m_Index = -1;
	m_convertedChars = 0;
	m_convertedChars2 = 0;
	m_Combo	= 0;
	m_Check = false;
	m_AnswerCheck = false;
	m_SumTime = 0.f;
	m_PivotTime = 4.0f;
	m_Speed = 400.f; //타수
	m_Velocity = m_Speed / 60.f; //평타 1초에 3타정도
	m_Wcstring = new wchar_t[ IN_MAX_LENGTH ];
	m_Wcstring2 = new wchar_t[ IN_MAX_LENGTH ];
	m_Input_position = 0;
	m_Len = 0;
	memset( m_InputString, 0, sizeof( m_InputString ) );
}

void NNInputEng::Label_Init()
{
	m_pContentString = NNLabel::Create( L"", L"3dumb", 30.f, 0xff0000 );
	m_pContentString->SetPosition( INPUT_POSITION_X, INPUT_POSITION_Y );
	m_pContentString->SetScale( 1.0f, 1.0f );

	m_pContentString2 = NNLabel::Create( L"", L"3dumb", 30.f, 0x0000ff );
	m_pContentString2->SetPosition( INPUT_POSITION_X, INPUT_POSITION_Y + 30 );
	m_pContentString2->SetScale( 1.0f, 1.0f);
}

void NNInputEng::File_Init()
{
	m_fin.open( "resource/input_file/input.txt" );
	m_fin >> m_DataCount;

	memset( m_InputStrings[ 0 ], 0, sizeof(m_InputStrings[ 0 ]) );
	m_fin.getline( m_InputStrings[ 0 ], sizeof( m_InputStrings[ 0 ] ) );
	
	int a[ STEP_STRING_COUNT ];

	for( int i=0; i<STEP_STRING_COUNT; ++i ) a[ i ] = i;
	
	for( int i=0; i<STEP_STRING_COUNT; ++i )
	{
		int r = rand() % 100;
		int temp = a[ i ];
		a[ i ] = a[ r ];
		a[ r ] = temp;
	}

	for( int i=0 ; i<STEP_STRING_COUNT; ++i )
	{
		memset( m_InputStrings[ a[ i ] ], 0, sizeof(m_InputStrings[ a[ i ] ]) );
		m_fin.getline( m_InputStrings[ a[ i ] ], sizeof( m_InputStrings[ a[ i ] ] ) );
	}
	m_DataCount = STEP_STRING_COUNT;
}

void NNInputEng::File_Close()
{
	m_fin.close();
}

void NNInputEng::Update(float dTime)
{
	m_SumTime += dTime;
	m_SpecialCheck = false;

	if( m_End ) return;

	NNObject::Update( dTime );

	if( m_SumTime >= m_PivotTime ) //50타씩 올려가자
	{
		m_Input_position = 0;
		m_Player_Input_String.clear();

		if( m_AnswerCheck == false )
			m_Combo = 0;

		m_AnswerCheck = false;
	
		++m_Index;

		if( m_Index < m_DataCount )
		{
			m_Len = strlen( m_InputStrings[ m_Index ] );

			m_PivotTime = static_cast<float>( m_Len )/ m_Velocity;
			m_SumTime = 0.f;

			mbstowcs_s( &m_convertedChars, m_Wcstring, IN_MAX_LENGTH, m_InputStrings[ m_Index ], _TRUNCATE );
			m_pContentString->SetString( m_Wcstring );
			_strupr_s( m_InputStrings[ m_Index ] );
			//
			memset( m_Playerstring, 0, sizeof( m_Playerstring ) );
			mbstowcs_s( &m_convertedChars, m_Wcstring2, IN_MAX_LENGTH, m_Playerstring, _TRUNCATE );
			m_pContentString2->SetString( m_Wcstring2 );
		}
		
	}

	//사용자가 어떤 키를 입력했는지 확인 하는 것

	if( ( m_InputStrings[ m_Index ][m_Input_position] != 0 ) && NNInputSystem::GetInstance()->GetKeyState( m_InputStrings[m_Index ][ m_Input_position ] ) == KEY_DOWN )
	{
		SetCheckAnswer( true );
		++m_Combo;
		++m_TotCombo;
		if( m_MaxCombo < m_Combo )
			m_MaxCombo = m_Combo;

		//std::cout << m_InputStrings[m_Index ][ m_Input_position ] << "정답입니다." << "콤보수 = " << m_Combo << " 입니다" << std::endl;
		//std::cout << m_InputStrings[m_Index ][ m_Input_position ] << " 을 입력하셨습니다      ," << m_Input_position << "    " << m_Len << std::endl;

		m_Player_Input_String += m_InputStrings[m_Index ][ m_Input_position ];
		//std::cout << "string " << m_Player_Input_String << std::endl;

		++m_Input_position;

		if( m_Input_position == m_Len ) //시간 내에 맞췄다
		{
			m_AnswerCheck = true;
			m_SpecialCheck = true;

			m_SumTime = m_PivotTime;

			memset( m_Playerstring, 0, sizeof( m_Playerstring ) );

			mbstowcs_s( &m_convertedChars, m_Wcstring2, IN_MAX_LENGTH, m_Playerstring, _TRUNCATE );

			m_pContentString2->SetString( m_Wcstring2 );
		}
		else
		{
			strcpy_s( m_Playerstring, m_Player_Input_String.c_str() );
			m_Player_Input_String[ strlen( m_Playerstring ) ] = '\0';

			mbstowcs_s( &m_convertedChars, m_Wcstring2, IN_MAX_LENGTH, m_Playerstring, _TRUNCATE );
			m_pContentString2->SetString( m_Wcstring2 );
		}
	}
	else if( NNInputSystem::GetInstance()->GetKeyState( VK_BACK ) == KEY_DOWN && m_Input_position > 0 )
	{
		--m_Input_position;
		m_Player_Input_String.erase( m_Player_Input_String.length() - 1 );

		strcpy_s( m_Playerstring, m_Player_Input_String.c_str() );

		mbstowcs_s( &m_convertedChars, m_Wcstring2, IN_MAX_LENGTH, m_Playerstring, _TRUNCATE );

		m_pContentString2->SetString( m_Wcstring2 );
	}
	else if( NNInputSystem::GetInstance()->IsDownAnyKey() == true && m_Index != -1 )
	{
		//std::cout << "틀렸다" << std::endl;
		m_Combo = 0;
		SetCheckAnswer( false );
	}
}

void NNInputEng::SetEnd(bool end)
{
	m_End = end;
	m_pContentString->SetVisible( false );
	m_pContentString2->SetVisible( false );
}