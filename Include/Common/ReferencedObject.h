#pragma once


NS_CH_BEG

class ReferencedObject : public Object
{
	CH_OBJ_TYPE_DECL(ReferencedObject,Object)
public:
	ReferencedObject();
	virtual ~ReferencedObject();
private://unable copy construct
	ReferencedObject(const ReferencedObject &);
	ReferencedObject &operator = (const ReferencedObject &);
public:
	void *operator new (size_t size)
	{
		ReferencedObject *pPointer = static_cast<ReferencedObject*>(MemoryManager::GetInstancePtr()->Malloc(size) );
		pPointer->m_nObjSize = size;
		return pPointer;
	}

	void operator delete(void *p)
	{
		ReferencedObject *pPointer = static_cast<ReferencedObject*>(p);
		MemoryManager::GetInstancePtr()->Free(p,pPointer->m_nObjSize);
	}

	inline void AddRef();
	inline void DeRef();
	inline void SetRef(int nRef);
	inline int GetRef() const;
	inline int GetObjectSize() const { return m_nObjSize; }
protected:
	int m_nObjSize;
	int m_nRefCount;
};



template <typename T> 
class Reference 
{
public:
	// Reference Public Methods
	Reference(T *p = NULL) 
	{
		ptr = p;
	}
	Reference(const Reference<T> &r) 
	{
		ptr = r.ptr;
		if (ptr)
		{
			ptr->AddRef();
		}
	}
	template<typename DerivedType>
	Reference(const Reference<DerivedType> &r)
	{
		ptr = r.GetPtr();
		if(ptr)
		{
			ptr->AddRef();
		}
	}

	Reference &operator=(const Reference<T> &r) 
	{
		if (r.ptr) r.ptr->AddRef();
		if (ptr) ptr->DeRef();
		ptr = r.ptr;
		return *this;
	}

	~Reference() 
	{
		if (ptr)
		{
			ptr->DeRef();
		}
	}
	T *operator->() { return ptr; }
	const T *operator->() const { return ptr; }
	operator bool() const { return ptr != NULL; }
	T *GetPtr() const { return ptr; }
private:
	T *ptr;
};

template<typename CastType,typename ObjType>
Reference<CastType> StaticCastPointer(Reference<ObjType> pObj)
{
	CastType *pT = static_cast<CastType*>(pObj.GetPtr());
	Reference<CastType> pRefObj = pT;
	return pRefObj;
}

inline void ReferencedObject::AddRef()
{
	Atomic::AtomicAdd(&m_nRefCount,1);
}

inline void ReferencedObject::DeRef()
{
	Atomic::AtomicAdd(&m_nRefCount,-1);
}

inline void ReferencedObject::SetRef(int nRef)
{
	Atomic::AtomicExchange(&m_nRefCount,nRef);
}

inline int ReferencedObject::GetRef() const
{
	return m_nRefCount;
}


NS_CH_END