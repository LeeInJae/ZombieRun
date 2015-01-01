#pragma once
#include "NNObject.h"

class NNAnimation;
class NNSound;

class NNZombie : public NNObject
{
public:
	NNZombie(void);
	~NNZombie(void);
	void ChangeAnimaition();
	void SetLife( int life ) { m_Life = life; }
	int  GetLife() { return m_Life; }
	void Update( float dTime );
	bool GetDieCheck() { return m_Die; }
	bool IsPlayAnimation();
private:
	void Init() {};
	void ZombieAnimationInit();
private:
	NNAnimation*	m_pZombie;
	NNAnimation*	m_pZombie_Die;
	NNSound*		m_DieSound;
	int				m_Life;
	bool			m_Die;
};

