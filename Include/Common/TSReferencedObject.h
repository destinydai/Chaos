#pragma once


NS_CH_BEG

class TSReferencedObject : public ReferencedObject
{
	CH_OBJ_TYPE_DECL(TSReferencedObject,ReferencedObject)
public:
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
};


NS_CH_END