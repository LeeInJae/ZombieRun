#include "NNSoundManager.h"


NNSoundManager* NNSoundManager::m_pInstance = nullptr;

NNSoundManager::NNSoundManager(void) : m_System(nullptr),m_Dchannel(nullptr), m_ZombieDieChannel(nullptr), m_BgmChannel(nullptr), m_ZombieChannel(nullptr)
{
	FMOD::System_Create(&m_System);
	m_System->init(32, FMOD_INIT_NORMAL, 0);
	Init();
}

NNSoundManager::~NNSoundManager(void)
{
	m_System->release();
	m_System->close();
}

void NNSoundManager::Init( void )
{
	SE_Sound[ BGM ] = CreateLoopSound("resource/sound/bgm.mp3");
	SE_Sound[ EXPLODE ] = CreateSound("resource/sound/explosion.mp3");
	SE_Sound[ ZOMBIE ] = CreateLoopSound("resource/sound/zombie.mp3");
	SE_Sound[ ZOMBIE_DIE ] = CreateLoopSound("resource/sound/zombie_death.mp3");
	SE_Sound[ ANSWER ] = CreateSound("resource/sound/answer.wav");
	SE_Sound[ WRONG ] = CreateSound("resource/sound/miss.wav");
}

void NNSoundManager::Close( void )
{
	m_System->close();
}

NNSoundManager* NNSoundManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new NNSoundManager();
	return m_pInstance;
}

void NNSoundManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

FMOD::Sound* NNSoundManager::CreateSound( std::string path )
{
	FMOD::Sound* sInstance;
	m_System->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &sInstance );
	return sInstance;
}


FMOD::Sound* NNSoundManager::CreateLoopSound( std::string path )
{
	FMOD::Sound* sInstance;
	m_System->createSound(path.c_str(), FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE, nullptr, &sInstance );
	return sInstance;
}

void NNSoundManager::Play( FMOD::Sound* sound )
{
	m_System->playSound(FMOD_CHANNEL_FREE, sound, false, &m_Dchannel);
}

void NNSoundManager::PlayAndGetChannel( FMOD:: Sound* sound, FMOD::Channel** channel )
{
	m_System->playSound(FMOD_CHANNEL_FREE, sound, false, channel);
}

void NNSoundManager::Pause( FMOD::Channel* channel )
{
	if (IsPlay(channel))
		channel->setPaused(true);
}


void NNSoundManager::Resume( FMOD::Channel* channel )
{
	if (IsPaused(channel))
		channel->setPaused(false);
}

bool NNSoundManager::IsPaused( FMOD::Channel* channel )
{
	bool isPaused;
	channel->getPaused(&isPaused);
	return isPaused;
}

void NNSoundManager::Reset( FMOD::Channel* channel )
{
	channel->setPosition(0, FMOD_TIMEUNIT_MS);
}

void NNSoundManager::Stop( FMOD::Channel* channel )
{
	if (IsPlay(channel))
	{
		channel->stop();
		Reset(channel);
	}
}

void NNSoundManager::SetVolume( FMOD::Channel* channel, float volume )
{
	channel->setVolume(volume);
}

bool NNSoundManager::IsPlay( FMOD::Channel* channel )
{
	bool isplay;
	channel->isPlaying(&isplay);
	return isplay;
}

void NNSoundManager::Update( float dTime )
{
	m_System->update();
}

















