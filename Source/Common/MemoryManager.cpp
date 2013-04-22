#include "stdafx.h"


NS_CH_BEG

MemoryManager::MemoryManager():m_allocator(nullptr),
	m_tsallocator(nullptr),
	m_nTotalMallocedSize(0)
{
	m_allocator = new MemoryPool(MALLOC_MAX_BLOCK_SIZE);
	m_tsallocator = new TSMemoryPool(MALLOC_MAX_BLOCK_SIZE);
}

MemoryManager::~MemoryManager()
{
	CH_SFDEL(m_allocator);
	CH_SFDEL(m_tsallocator);
}

	
MemoryManager * MemoryManager::GetInstancePtr()
{
	static MemoryManager mgr;
	return &mgr;
	return 0;
}

void *MemoryManager::Malloc( size_t nBytes )
{
	return m_allocator->Malloc(nBytes);
}

void MemoryManager::Free( void *p, size_t nBytes )
{
	return m_allocator->Free(p,nBytes);
}

void * MemoryManager::SafeMalloc( size_t nBytes )
{
	return m_tsallocator->Malloc(nBytes);
}

void MemoryManager::SafeFree( void *p,size_t nBytes )
{
	m_tsallocator->Free(p,nBytes);
}



NS_CH_END