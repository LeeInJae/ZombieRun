#pragma once
#include "NNScene.h"
#include <string>
#include <fstream>
#include "PRE_DEFINE.h"

class NNSprite;
class NNLabel;
class NNAnimation;
class NNPlayerCharacter;
class NNZombie;
class NNInputEng;
class NNSound;
class NNPlain;

class NNStartScene : public NNScene
{
public:
	NNStartScene(void);
	~NNStartScene(void);

private:
	void Init() {};
	void Update( float dTime );
	void		 UI_Init();
	void		 Number_Init();
	void		 Position_Init();
	void		 Class_Init();
	void		 Render();
	//bool		 IsCollision( Hit_Square a, Hit_Square b );
private:
	NNSprite*			m_pBackGround[ 2 ];
	NNLabel*			m_pReadyTime;
	NNLabel*			m_pContentString;
	NNZombie*			m_pZombie;
	NNPlayerCharacter*	m_pCharacter;
	NNPlain*			m_pPlain;

	NNInputEng*			m_pInputEng;
	NNSound*			m_ZombieSound;
	NNSound*			m_EndBgm;
	wchar_t*			m_pInputString;
	wchar_t				m_ReadyTime[ 20 ];
	
	char				m_InputString[ IN_MAX_LENGTH ];
	float				m_SumTime;
	float				m_LevelTime;
	bool				m_CheckTime;
	bool				m_EndSoundCheck;
	//bool				m_End;

	wchar_t				m_PlayTimeString[20];
	NNLabel*			m_ElapsedPlayTimeLabel;

	int					m_TimePositionCheck;
	int					m_CorrectCount;
	float				m_Point;
	wchar_t				m_PointString[20];
	NNLabel*			m_pPointLabel;	

	wchar_t				m_ComboString[20];
	NNLabel*			m_pComboLabel;


	NNSound*			m_Bgm;
	NNSound*			m_AnswerSound;
	NNSound*			m_WrongSound;
	NNSound*			m_MissileSound;
};