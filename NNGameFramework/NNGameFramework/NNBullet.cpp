#include "NNBullet.h"


NNBullet::NNBullet(void)
{
}


NNBullet::~NNBullet(void)
{
}

bool NNBullet::CheckLifeTime()
{
	if( m_ElapsedTime >= m_LifeTime )
		return true;
	return false;
}

void NNBullet::Update(float dTime)
{
	NNObject::Update( dTime );
	m_ElapsedTime += dTime;
}
