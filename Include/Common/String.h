#pragma once


NS_CH_BEG

namespace StringUtl
{
	
}


	//const char *p �İ�װ�����´����
class StringPtr
{
public:
	StringPtr(const char *szStr):m_data(szStr),m_size(0)
	{CH_ASSERT(m_data);}
	StringPtr(const char *szStr,uint n):m_data(szStr),m_size(n)
	{CH_ASSERT(m_data && m_size!=0);}
	~StringPtr()
	{m_data=nullptr;m_size=0;}

	StringPtr(const StringPtr &str)
	{m_data = str.m_data;m_size = str.m_size;}

	char operator[](uint index) const
	{
		return m_data[index];
	}

	StringPtr &operator = (const StringPtr &str)
	{m_data = str.m_data;m_size = str.m_size; return *this;}

	bool operator == (const StringPtr &str) const 
	{return strcmp(m_data,str.m_data) == 0;}

	bool operator != (const StringPtr &str) const
	{return strcmp(m_data,str.m_data) != 0; }

	bool operator == (const char *szStr) const
	{ return strcmp(m_data,szStr)==0; }

	bool operator != (const char *szStr) const
	{return strcmp(m_data,szStr)!=0;}

	bool operator < (const StringPtr &str) const 
	{CH_ASSERT(false);}

	bool empty() const 
	{ return m_data!=0; }

	uint size()  
	{ 
		if(m_size==0)
			m_size = strlen(m_data);
		return m_size; 
	}

	bool startWith(const char *szStr,bool caseSensitive=true) const
	{
		CH_ASSERT(false);
	}
	bool endWith(const char *szStr,bool caseSensitive=true) const
	{
		CH_ASSERT(false);
	}

	const char *data() const { return m_data; }

private:
	const char *m_data;
	uint m_size;
};

class String
{
public:
	String():m_data(nullptr),m_size(0)
	{}

	String(const char *szString):m_data(0),m_size(0)
	{
		copy(szString);
	}
	
	String(const String &str):m_data(0),m_size(0)
	{
		copy(str.m_data);
	}

	String &operator = (const String &str)
	{
		copy(str.m_data);
		return *this;
	}

	~String()
	{ CH_SFDELARR(m_data); m_size=0; }

	char &operator[](uint index)
	{
		CH_ASSERT(m_data!=nullptr && index < m_size);
		return m_data[index];
	}

	char operator[](uint index) const
	{ return (*this)[index]; }

	operator StringPtr() const
	{
		return StringPtr(m_data,m_size);
	}

	uint size() const
	{ return m_size; }

	bool empty() const 
	{ return m_data!=nullptr; }

	void copy(const char *szString)
	{
		CH_SFDELARR(m_data);
		if(szString!=nullptr)
		{
			m_size = strlen(szString);
			m_data = new char[m_size+1];
			memcpy(m_data,szString,m_size+1);
		}
		else
		{
			m_size = 0;
		}
		
	}

	bool operator == (const String &str) const 
	{
		return strcmp(m_data,str.m_data) == 0;
	}

	bool operator != (const String &str) const
	{
		return strcmp(m_data,str.m_data) != 0;
	}

	bool operator == (const char *szStr) const
	{
		return strcmp(m_data,szStr)==0;
	}

	bool operator != (const char *szStr) const
	{
		return strcmp(m_data,szStr)!=0;
	}

	bool operator == (const StringPtr &s) const
	{ return strcmp(m_data,s.data())==0; }

	bool operator != (const StringPtr &s) const 
	{ return strcmp(m_data,s.data())!=0; }

	bool operator < (const String &str) const 
	{
		CH_ASSERT(false);
	}

	bool startWith(const char *szStr,bool caseSensitive=true) const
	{ StringPtr s(m_data); return s.startWith(szStr,caseSensitive);}

	bool endWith(const char *szStr,bool caseSensitive=true) const
	{ StringPtr s(m_data); return s.endWith(szStr,caseSensitive); }

	char *data() { return m_data; }

	const char *c_str() const { return m_data; }

	void toUpperCase()
	{

	}

	void toLowerCase()
	{

	}

private:
	char *m_data;
	uint m_size;
};


NS_CH_END
