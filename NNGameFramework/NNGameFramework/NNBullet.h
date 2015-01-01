#pragma once
#include "nnobject.h"

class NNAnimation;

class NNBullet : public NNObject
{
public:
	NNBullet(void);
	~NNBullet(void);
	bool CheckLifeTime();
	virtual void Update( float dTime );
	void Init(){}

protected:
	NNAnimation*	m_Bullet;
	float			m_ElapsedTime;
	float			m_LifeTime;
};

