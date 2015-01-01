#pragma once
#include "nnobject.h"
#include "PRE_DEFINE.h"

class NNEffect;
class NNEffectManager : public NNObject
{
public:
	static NNEffectManager* GetInstance();
	static void ReleaseInstance();
	void Update( float dTime );
	void Init(){};

	void MakeEffect( EFFECT_KIND kind, float position_x, float position_y );
	void RemoveEffectCheck();
	
	std::list< NNEffect* >& GetEffectList(){ return m_EffectList; } //읽기전용 리스트반환
private:
	NNEffectManager(void);
	~NNEffectManager(void);

private:
	static NNEffectManager* m_pInstance;
	std::list< NNEffect* > m_EffectList;
};