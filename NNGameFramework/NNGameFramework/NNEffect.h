#pragma once
#include "nnobject.h"

class NNAnimation;

class NNEffect : public NNObject
{
public:
	NNEffect(void);
	~NNEffect(void);
	bool CheckLifeTime();
	virtual void Update( float dTime );
	void Init(){}
protected:
	NNAnimation*	m_Effect;
	float			m_ElapsedTime;
	float			m_LifeTime;
};

