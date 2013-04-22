#pragma once


NS_CH_BEG

class TSMemoryPoolFixed : public MemoryPoolFixed
{
public:
	inline TSMemoryPoolFixed(uint nBlockSize,uint nBlockCount):MemoryPoolFixed(nBlockSize,nBlockCount)
	{

	}

	inline ~TSMemoryPoolFixed()
	{

	}

	inline void *Malloc()
	{
		CriticalSection::ScopeLock lock(m_cs);
		return MemoryPoolFixed::Malloc();
	}

	inline void Free(void *pData)
	{
		CriticalSection::ScopeLock lock(m_cs);
		MemoryPoolFixed::Free(pData);
	}

	inline bool IsFromThis(void *p)  
	{
		CriticalSection::ScopeLock lock(m_cs);
		MemoryPoolFixed::IsFromThis(p);
	}

	inline uint BlockSize() 
	{
		CriticalSection::ScopeLock lock(m_cs);
		return MemoryPoolFixed::BlockSize();
	}
private:
	CriticalSection m_cs;
};

NS_CH_END