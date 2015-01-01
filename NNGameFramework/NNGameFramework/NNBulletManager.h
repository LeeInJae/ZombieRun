#pragma once
#include "nnobject.h"
#include "PRE_DEFINE.h"

class NNBullet;
class NNZombie;
class NNSound;

class NNBulletManager : public NNObject
{
public:
	static NNBulletManager* GetInstance();
	static void ReleaseInstance();
	void Update( float dTime );
	void Init() {};
	void MakeBullet( BULLET_KIND kind );
	void RemoveBulletCheck();
	void Zombie_Bullet_HitCheck( NNZombie* pZombie );
	std::list< NNBullet* >& GetBulletLIst(){ return m_BulletList; }
private:
	NNBulletManager(void);
	~NNBulletManager(void);
private:
	static NNBulletManager*	m_pInstance;
	std::list< NNBullet* > m_BulletList;
	NNSound*			   m_Explode;
};