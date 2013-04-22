#pragma once

NS_CH_BEG

class MemoryPool;
class TSMemoryPool;

class MemoryManager
{
public:
	enum
	{
		MALLOC_MAX_BLOCK_SIZE = 1024 * 1024 * 16
	};
protected:
	MemoryManager();
	~MemoryManager();
public:
	uint64 GetTotalMallocedSize() const  { return m_nTotalMallocedSize; }

	static MemoryManager *GetInstancePtr();

	//Not thread safe malloc
	void *Malloc(size_t nBytes);
	void Free(void *p, size_t nBytes);
	//Thread safe malloc
	void *SafeMalloc(size_t nBytes);
	void SafeFree(void *p,size_t nBytes);
public://inner use
	inline void AddMallocBytes(int nBytes) { Atomic::AtomicAdd((int64*)&m_nTotalMallocedSize,nBytes); }
private:
	int64 m_nTotalMallocedSize;
	MemoryPool *m_allocator;
	TSMemoryPool *m_tsallocator;
};


NS_CH_END
