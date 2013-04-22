#pragma once


NS_CH_BEG

class MemoryPoolFixed
{
public:
	inline MemoryPoolFixed(uint nBlockSize,uint nBlockCount):
		m_nBlockSize(nBlockSize),m_vecBlocks(nBlockCount)
	{
		CH_ASSERT(m_nBlockSize&&nBlockCount);
		for(uint i=0; i<nBlockCount; ++i)
		{
			m_vecBlocks[i] = new char[m_nBlockSize];
			m_setBlocks.insert(m_vecBlocks[i]);
		}
		MemoryManager::GetInstancePtr()->AddMallocBytes(nBlockCount * m_nBlockSize);
	}
	inline ~MemoryPoolFixed()
	{
		CH_ASSERT(m_setBlocks.size() == m_vecBlocks.size(),"blocks not equal there must be some block not return back to the pool!");
		MemoryManager::GetInstancePtr()->AddMallocBytes(-((int)(m_setBlocks.size()  * m_nBlockSize)));
		for(auto itr=m_setBlocks.begin(); itr!=m_setBlocks.end(); ++itr)
		{
			delete [] (*itr);
		}
	}

private:// forbid to copy construct
	MemoryPoolFixed(const MemoryPoolFixed &);
	inline MemoryPoolFixed &operator=(const MemoryPoolFixed &);
public:
	inline void *Malloc()
	{
		if(m_vecBlocks.size() == 0)
		{
			MemoryManager::GetInstancePtr()->AddMallocBytes(m_setBlocks.size()  * m_nBlockSize);
			m_vecBlocks.reserve(m_setBlocks.size() << 1);
			for(uint i=m_setBlocks.size(); i<m_vecBlocks.size(); ++i)
			{
				char *p = new char[m_nBlockSize];
				m_vecBlocks.push_back(p);
				m_setBlocks.insert(p);
			}
		}

		void *p = *m_vecBlocks.end();
		m_vecBlocks.pop_back();
		return p;
	}

	inline void Free(void *pData)
	{
		CH_ASSERT(pData,"return a null pointer!");
		CH_ASSERT(IsFromThis(pData),"this block of memory is not from this.");
		m_vecBlocks.push_back((char*)pData);
	}

	inline bool IsFromThis(void *p) const 
	{
		std::set<char*>::const_iterator itr = m_setBlocks.find((char*)p);
		return itr!=m_setBlocks.end();
	}

	inline uint BlockSize() const { return m_nBlockSize; }

private:
	uint m_nBlockSize;
	std::vector<char*> m_vecBlocks;
	std::set<char*> m_setBlocks;
};


NS_CH_END
