#include "NNDefaultBullet.h"
#include "NNAnimation.h"
#include "PRE_DEFINE.h"


NNDefaultBullet::NNDefaultBullet(void)
{
	m_LifeTime = 0.3f * 8;
	m_x = PLAIN_SHOOT_POSITION_X;
	m_ElapsedTime = 0.f;
	m_Bullet = NNAnimation::Create( 8, DEFAULT_BULLET_0, DEFAULT_BULLET_1, DEFAULT_BULLET_2,
		DEFAULT_BULLET_3, DEFAULT_BULLET_4, DEFAULT_BULLET_5, DEFAULT_BULLET_6, DEFAULT_BULLET_7 );
	m_Bullet->SetFrameTime( 0.1f ); 
	m_Bullet->SetZindex( 3 );
	LineEqu();
	AddChild( m_Bullet );
}

NNDefaultBullet::~NNDefaultBullet(void)
{
}

void NNDefaultBullet::Update( float dTime )
{
	NNBullet::Update( dTime );

	m_x -= ( dTime * 500.f );
	m_y = m_a * ( m_x - PLAIN_SHOOT_POSITION_X ) + PLAIN_SHOOT_POSITION_Y;

	//m_Bullet->SetPosition( m_x, m_y );
	//SetPosition( 100 - dTime * 10.f, 100 - dTime * 10.f );
	SetPosition( m_x, m_y );
}

void NNDefaultBullet::LineEqu()
{
	float plain_x, plain_y, zombie_x, zombie_y;

	plain_x		=	PLAIN_SHOOT_POSITION_X;  //x1,
	plain_y		=	PLAIN_SHOOT_POSITION_Y;//y1
	zombie_x	=	rand() % ( ZOMBIE_TARGET_POSITION_MAX_X - ZOMBIE_TARGET_POSITION_MIN_X ) + ZOMBIE_TARGET_POSITION_MIN_X;//x2
	zombie_y	=	rand() % ( ZOMBIE_TARGET_POSITION_MAX_Y - ZOMBIE_TARGET_POSITION_MIN_Y ) + ZOMBIE_TARGET_POSITION_MIN_Y;//y2

	m_a = ( zombie_y - plain_y ) / (zombie_x - plain_x ); //±â¿ï±â
}
