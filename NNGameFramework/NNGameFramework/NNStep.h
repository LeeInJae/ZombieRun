#pragma once
#include "nnscene.h"
#include "PRE_DEFINE.h"

class NNSprite;
class NNLabel;

class NNStep : public NNScene
{
public:
	NNStep(void);
	~NNStep(void);

private:
	void Init() {};
	void Update( float dTime );

private:
	STEP		m_Toggle;
	NNSprite*	m_pBackground;
	NNLabel*	m_pStep[ STEP_COUNT ];
	float		m_DelayTime;
	wchar_t		m_StepCharacter[ STEP_COUNT ][ 20 ];
};

