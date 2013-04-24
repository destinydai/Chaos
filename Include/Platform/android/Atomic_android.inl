
inline int Atomic::WaitForValueEqual( int* var, int value )
{
	volatile int *pVar = (volatile int *)var;
	int nRet;
	while( (nRet=*pVar)!=value)
	{
		usleep(0);
	}
	return nRet;
}

inline int Atomic::WaitForValueNotEqual( int* var, int value )
{
	volatile int *pVar = (volatile int *)var;
	int nRet;
	while( (nRet=*pVar)==value)
	{
		usleep(0);
	}
	return nRet;
}

inline int Atomic::AtomicAdd(volatile int* var, int value )
{
	if(value>0)
	{
		return __sync_fetch_and_add(var,value);
	}
	else
	{
		return __sync_fetch_and_sub(var,-value);
	}
}

inline int Atomic::AtomicExchange(volatile int *var, int value )
{
	return __atomic_swap(value,var);
}

inline int64 Atomic::AtomicAdd(volatile int64* var, int64 value )
{
	(*var)+=value;
	return *var;
}

inline int64 Atomic::AtomicExchange(volatile int64 *var, int64 value )
{
	(*var)=value;
	return *var;
}

