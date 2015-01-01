#pragma once
#include "nnbullet.h"
class NNDefaultBullet : public NNBullet
{
public:
	NNDefaultBullet(void);
	~NNDefaultBullet(void);
	void Update( float dTime );

private:
	void Init(){}
	void LineEqu();
	float m_y, m_x, m_a;
};

