#pragma once

NS_CH_BEG

class TSMemoryPool : public MemoryPool
{
public:
	TSMemoryPool(uint nMaxBlockSize):MemoryPool(nMaxBlockSize)
	{

	}
	~TSMemoryPool()
	{

	}

	void *Malloc(size_t nSize)
	{
		CriticalSection::ScopeLock lock(m_cs);
		return MemoryPool::Malloc(nSize);
	}
	void Free(void *p, size_t nSize)
	{
		CriticalSection::ScopeLock lock(m_cs);
		MemoryPool::Free(p,nSize);
	}
private:
	CriticalSection m_cs;
};


NS_CH_END