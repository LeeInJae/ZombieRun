#include "NNMapManager.h"
#include "NNSprite.h"
#include "PRE_DEFINE.h"

NNMapManager* NNMapManager::m_pInstance = nullptr;

NNMapManager::NNMapManager(void)
{
	m_pScore = NNSprite::Create( SCORE_SPRITE );
	m_pScore->SetZindex( 0 );
	m_pScore->SetScaleX( 1.5f );
	m_pBackGround[ 0 ] = NNSprite::Create( BACKGROUND_SPRITE1 );
	m_pBackGround[ 1 ] = NNSprite::Create( BACKGROUND_SPRITE2 );

	m_pBackGround[ 0 ]->SetImageWidth( GAME_WIDTH );
	m_pBackGround[ 0 ]->SetImageHeight( GAME_HEIGHT );
	m_pBackGround[ 0 ]->SetPosition( 0, 0 );

	m_pBackGround[ 1 ]->SetImageWidth( GAME_WIDTH );
	m_pBackGround[ 1 ]->SetImageHeight( GAME_HEIGHT );
	m_pBackGround[ 1 ]->SetPosition( 800, 0 );

	m_pBackGround[ 0 ]->SetZindex( 0 );
	m_pBackGround[ 1 ]->SetZindex( 0 );
	for( int i=0; i<BACKGROUND_NUMBER; ++i )
		AddChild( m_pBackGround[ i ] );
	AddChild( m_pScore );
}


NNMapManager::~NNMapManager(void)
{
}

NNMapManager* NNMapManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new NNMapManager;
	}
	return m_pInstance;
}

void NNMapManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void NNMapManager::Update(float dTime)
{
	float dX0, dY0;
	dX0 = m_pBackGround[ 0 ]->GetPositionX(); //1�� ��������Ʈ�� ������
	dY0 = m_pBackGround [ 0 ]->GetPositionY();

	if(dX0 < -GAME_WIDTH )
	{
		dX0 = 0;
		NNSprite* temp = m_pBackGround[0];//1�� ��������Ʈ�� �̹����� ȭ������� ������ �ڿ������� ���� ��������Ʈ�� �̾��־� �������� ����
		m_pBackGround[0] = m_pBackGround[1]; 
		m_pBackGround[1] = temp;
	}
	else
	{
		dX0 -= ( dTime * 100); //�ӵ� 100���� ���� �޸��� ����
		m_pBackGround[0]->SetPosition( dX0 , dY0 );
	}

	m_pBackGround[ 0 ]->SetPosition( dX0 , dY0 );//�ռ� ��������Ʈ ��ġ
	m_pBackGround[ 1 ]->SetPosition( dX0 + GAME_WIDTH , dY0);//�ڿ� �ڿ������� �ٿ��� ������� ��������Ʈ
}