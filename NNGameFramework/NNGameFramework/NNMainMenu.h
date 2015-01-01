#pragma once
#include "NNScene.h"
#include "PRE_DEFINE.h"
#include "Library/FMOD/inc/fmod.h"
#include "Library/FMOD/inc/fmod.hpp"
#include "Library/FMOD/inc/fmod_errors.h"

class NNSprite;
class NNAnimation;
class NNLabel;
class NNSound;

class NNMainMenu : public NNScene
{
public:
	NNMainMenu(void);
	~NNMainMenu(void);

private:
	void Init() { };
	void Update( float dTime );
private:
	NNSprite*		 m_pBackground;
	NNSprite*		 m_pBackboard;
	NNAnimation*	 m_pZombie;
	NNAnimation*	 m_pCharacter;
	NNLabel*		 m_pMenu[ MENU_COUNT ];
	NNSound*		 m_Bgm;
	MENU			 m_Toggle;
	float			 m_DelayTime;
};