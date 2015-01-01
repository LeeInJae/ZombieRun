#pragma once
#include "nnscene.h"

class NNSprite;
class NNLabel;

class NNEnd : public NNScene
{
public:
	NNEnd(void);
	NNEnd( int point, int combo, int tot_combo );
	~NNEnd(void);

private:
	virtual void Init(){};
	virtual void Update( float dTime );

private:
	NNSprite*	m_pBackground;
	float		m_SumTime;
	NNLabel*	m_pPoint;
	NNLabel*	m_pCombo;
	NNLabel*	m_pClear;
	NNLabel*	m_pTotCombo;
	wchar_t		m_TotCombo[ 20 ];
	wchar_t		m_Point[ 20 ];
	wchar_t		m_Combo[ 20 ];
};

