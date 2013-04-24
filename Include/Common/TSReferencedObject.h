#pragma once


NS_CH_BEG

class TSReferencedObject : public Object
{
	CH_OBJ_TYPE_DECL(TSReferencedObject,Object)
protected:
	TSReferencedObject();
	virtual ~TSReferencedObject();
public:
	void *operator new (size_t size)
	{
		TSReferencedObject *pPointer = static_cast<TSReferencedObject*>(MemoryManager::GetInstancePtr()->SafeMalloc(size) );
		pPointer->m_nObjSize = size;
		return pPointer;
	}

	void operator delete(void *p)
	{
		TSReferencedObject *pPointer = static_cast<TSReferencedObject*>(p);
		MemoryManager::GetInstancePtr()->SafeFree(p,pPointer->m_nObjSize);
	}

	inline void AddRef();
	inline void DeRef();
	inline void SetRef(int nRef);
	inline int GetRef() const;
	inline int GetObjectSize() const { return m_nObjSize; }

protected:
	volatile int m_nObjSize;
	volatile int m_nRefCount;
};


inline void TSReferencedObject::AddRef()
{
	Atomic::AtomicAdd(&m_nRefCount,1);
}

inline void TSReferencedObject::DeRef()
{
	Atomic::AtomicAdd(&m_nRefCount,-1);
	if(m_nRefCount<=0){
		delete this;
	}
}

inline void TSReferencedObject::SetRef(int nRef)
{
	Atomic::AtomicExchange(&m_nRefCount,nRef);
}

inline int TSReferencedObject::GetRef() const
{
	return m_nRefCount;
}


NS_CH_END