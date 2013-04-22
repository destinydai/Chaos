

class CallableBase
{
public:
};


//callable void return and void input
template<typename T>
class Callable : public CallableBase
{
public:
	typedef void(T::*Pfn)();
public:
	Callable(Pfn pfn, T* pObj):m_pObj(pObj),m_pCallback(pfn){		
	}
	void Invoke(){
		return (m_pObj->*m_pCallback)();
	}
private:
	Pfn m_pCallback;
	T* m_pObj;
};

template<typename R >
class Function
{
public:
	typedef void (CallableBase::*PfnNN)();
public:
	Function(PfnNN pCallback, CallableBase* pObj):
	  m_pObj(pObj),
	 m_pCallable(pCallback){		
	}

	~Function(){
		if(m_pObj){
			//delete m_pObj;
			m_pObj = 0;
		}
	}
public:
	void Invoke()
	{
		return (m_pObj->*m_pCallable)();
	}
private:
	PfnNN m_pCallable;
	CallableBase* m_pObj;
};


template<typename T, typename R>
Function<void()> CreateDelegate(R(T::*pfn)(),T* pObj)
{
	typedef Function<R()> ReturnFunction;
	CallableBase* pBase = new Callable<T>(pfn,pObj);
	return ReturnFunction((ReturnFunction::PfnNN)&Callable<T>::Invoke ,pBase) ;
}

/*
template<typename T, typename R>
Function<R()> CreateDelegate(R(T::*pfn)(),T* pObj)
{
	typedef Function<R()> ReturnFunction;
	CallableBase* pBase = new Callable<T>(pfn,pObj);

}
*/