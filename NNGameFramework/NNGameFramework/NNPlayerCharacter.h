#pragma once
#include "NNObject.h"

class NNAnimation;

class NNPlayerCharacter : public NNObject
{
public:
	NNPlayerCharacter(void);
	~NNPlayerCharacter(void);

	float GetBackSpeed(){ return m_BackSpeed; }
	float GetFrontSpeed(){ return m_FrontSpeed; }
	float GetWrongAnswerSpeed(){ return m_WrongAnswerSpeed; }
	void SetBackSpeed( float speed) { m_BackSpeed = speed; }
private:
	void Init() {};	
	void CharacterAnimationInit();
private:
	NNAnimation*	m_pCharacter;
	float			m_BackSpeed;
	float			m_FrontSpeed;
	float			m_WrongAnswerSpeed;
};

