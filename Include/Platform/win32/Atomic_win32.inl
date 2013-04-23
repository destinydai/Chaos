

inline int Atomic::WaitForValueEqual( int* var, int value )
{
	volatile int *pVar = (volatile int *)var;
	int nRet;
	while( (nRet=*pVar)!=value)
	{
		::Sleep(0);
	}
	return nRet;
}

inline int Atomic::WaitForValueNotEqual( int* var, int value )
{
	volatile int *pVar = (volatile int *)var;
	int nRet;
	while( (nRet=*pVar)==value)
	{
		::Sleep(0);
	}
	return nRet;
}


inline int Atomic::AtomicAdd(volatile  int* var, int value )
{
	return InterlockedExchangeAdd((LONG*)var,value);
}

inline int Atomic::AtomicExchange(volatile  int *var, int value )
{
	return InterlockedExchange((LONG*)var,value);
}

inline int64 Atomic::AtomicAdd(volatile  int64* var, int64 value )
{
	return InterlockedExchangeAdd64((LONGLONG*)var,value);
}

inline int64 Atomic::AtomicExchange(volatile  int64 *var, int64 value )
{
	return InterlockedExchange64((LONGLONG*)var,value);
}