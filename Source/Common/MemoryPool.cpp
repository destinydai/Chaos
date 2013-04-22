#include "stdafx.h"
#include <algorithm>

NS_CH_BEG

MemoryPool::MemoryPool( uint nMaxBlockSize ):
	m_nMaxAllocSize(nMaxBlockSize),
	m_nMinAllocSize(16)
{
	int nAlloSize = m_nMaxAllocSize / m_nMinAllocSize;
	m_nMaxAllocSize = nAlloSize * m_nMinAllocSize;
	uint nMemSize = m_nMinAllocSize;
	nAlloSize = 0;
	while(nMemSize<m_nMaxAllocSize)
	{
		++nAlloSize;
		nMemSize = m_nMinAllocSize << nAlloSize;
	}

	m_allocators.resize(nAlloSize);

	nMemSize=0;
	for(int i=0,j=0; i<nAlloSize; ++i,++j)
	{
		nMemSize = m_nMinAllocSize<<j;
		m_allocators[i] = new MemoryPoolFixed(nMemSize,8);
	}
}

MemoryPool::~MemoryPool()
{
	for(uint i=0; i<m_allocators.size(); ++i)
	{
		CH_SFDEL(m_allocators[i]);
	}
}


inline bool BinarySerachPred(uint nMemSize,MemoryPoolFixed* lhs)
{
	if(lhs->BlockSize()>=nMemSize)
	{
		return true;
	}
	return false;
}

void * MemoryPool::Malloc( size_t nSize )
{
	std::vector<MemoryPoolFixed*>::iterator pos =std::upper_bound(m_allocators.begin(),m_allocators.end(),nSize,BinarySerachPred);
	if(pos!=m_allocators.end())
	{
		return (*pos)->Malloc();
	}

	return operator new(nSize);
}

void MemoryPool::Free( void *p, size_t nSize )
{
	std::vector<MemoryPoolFixed*>::iterator pos =std::upper_bound(m_allocators.begin(),m_allocators.end(),nSize,BinarySerachPred);
	if(pos!=m_allocators.end())
	{
		(*pos)->Free(p);
	}
	else
	{
		operator delete(p);
	}
}



NS_CH_END
