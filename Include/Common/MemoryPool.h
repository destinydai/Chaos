#pragma once


NS_CH_BEG

class MemoryPool
{
public:
	MemoryPool(uint nMaxBlockSize);
	virtual ~MemoryPool();
private:
	MemoryPool(const MemoryPool &);
	MemoryPool &operator==(const MemoryPool &);
public:
	void *Malloc(size_t nSize);
	void Free(void *p, size_t nSize);
private:
	std::vector<MemoryPoolFixed*> m_allocators;
	uint m_nMinAllocSize;
	uint m_nMaxAllocSize;
};

NS_CH_END