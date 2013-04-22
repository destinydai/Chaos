


inline CriticalSection::CriticalSection(int spinCount )
{
	if(spinCount==0)
		spinCount = 4000;
	InitializeCriticalSectionAndSpinCount(&m_section,spinCount);
}

inline CriticalSection::~CriticalSection()
{
	DeleteCriticalSection(&m_section);
}

inline void CriticalSection::enter()
{
	EnterCriticalSection(&m_section);
}

inline void CriticalSection::leave()
{
	LeaveCriticalSection(&m_section);
}