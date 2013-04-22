#include "stdafx.h"


NS_CH_BEG

GraphicsManager::GraphicsManager( IRenderDevice *pDevice ):
	m_pRender(pDevice)
{

}

GraphicsManager::~GraphicsManager( void )
{

}

void GraphicsManager::Create( IRenderDevice *pDevice )
{
	CH_ASSERT(pDevice);

	if(m_pInstance)
		return;
	m_pInstance = new GraphicsManager(pDevice);
}

void GraphicsManager::Destroy( void )
{
	CH_SFDEL(m_pInstance);
}

NS_CH_END