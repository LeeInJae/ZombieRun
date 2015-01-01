#include "NNInputManager.h"

NNInputManager* NNInputManager::m_pInstance = nullptr;

NNInputManager::NNInputManager(void)
{
}

NNInputManager::~NNInputManager(void)
{
}

NNInputManager* NNInputManager::GetInstance()
{
	if( m_pInstance == nullptr )
	{
		m_pInstance = new NNInputManager();
		return m_pInstance;
	}
	return m_pInstance;
}

void NNInputManager::Init()
{

}

void NNInputManager::Update(float dTime)
{
	NNObject::Update( dTime );
}

void NNInputManager::ReleaseInstance()
{
	if( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
