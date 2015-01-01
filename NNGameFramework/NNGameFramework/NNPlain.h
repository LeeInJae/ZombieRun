#pragma once
#include "nnobject.h"

class NNAnimation;

class NNPlain : public NNObject
{
public:
	NNPlain(void);
	~NNPlain(void);


private:
	void Init(){};
	void PlainAnimationInit();
	NNAnimation*	m_pPlain;
};

