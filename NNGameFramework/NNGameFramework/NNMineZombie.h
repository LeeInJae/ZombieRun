#pragma once
#include "nnobject.h"

class NNAnimation;

class NNMineZombie : public NNObject
{
public:
	NNMineZombie(void);
	~NNMineZombie(void);
	NNCREATE_FUNC( NNMineZombie );

	
private:
	void Init() {};
	void ZombieAnimationInit();
private:
	NNAnimation*	m_pMine_Zombie;
};