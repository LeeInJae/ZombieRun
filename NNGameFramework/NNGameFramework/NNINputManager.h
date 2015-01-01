#pragma once
#include "NNObject.h"

class NNInputManager : public NNObject
{
public:
	NNCREATE_FUNC( NNInputManager );
	static NNInputManager*	GetInstance();
	static void				ReleaseInstance();

private:
	NNInputManager(void);
	~NNInputManager(void);

	virtual void Init();
	virtual void Update( float dTime );
private:
	static NNInputManager*	m_pInstance;

};

