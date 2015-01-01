#pragma once
#include "NNObject.h"

class NNSprite;

class NNMapManager : public NNObject
{
public:
	static NNMapManager* GetInstance();
	static void ReleaseInstance();
	void Update( float dTime );
	void Init() {};
private:
	NNMapManager(void);
	~NNMapManager(void);
	static NNMapManager* m_pInstance;

private:
	NNSprite*	m_pBackGround[ 2 ];
	NNSprite*	m_pScore;
};

