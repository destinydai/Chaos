#pragma once

#include <vector>

NS_CH_BEG

/*
template<typename T>
class Array
{
	typedef T* iterator;
	typedef const T* const_iterator;
public:
	Array():m_data(nullptr),m_size(0),m_capacity(0) {}

	Array(uint capacity):m_data(nullptr),m_size(0),m_capacity(0)
	{
		reserve(capacity);
	}

	Array(iterator beg, iterator end):m_data(0),m_size(0),m_capacity(0)
	{
		CH_ASSERT(beg!=nullptr && end !=nullptr && end >= beg);
		m_capacity = end - beg;
		reserve(m_capacity);
		iterator sItr = this->begin();
		for(iterator itr=beg; itr!=end; ++itr,++sItr)
		{
			*sItr = *itr;
		}
		m_size = m_capacity;
	}

	Array(const Array &a):m_data(nullptr),m_size(a.size()),m_capacity(a.size())
	{
		m_data = new T[this->capacity()];
		for(uint i=0; i<size(); ++i)
		{
			m_data[i] = a.m_data[i];
		}
	}

	~Array()
	{
		CH_SFDELARR(m_data);
		m_size=0;
	}

	T &operator[](uint index)
	{
		CH_ASSERT(index<m_size;)
		return m_data[index];
	}

	const T &operator[](uint index) const
	{
		return (*this)[index];
	}

	uint size() const { return m_size; }
	bool empty() const { return m_data!=0; }
	uint capacity() const { return m_capacity; }
	void reserve(uint capacity)
	{
		CH_ASSERT(capacity>0);

		if(m_data==nullptr)
		{
			m_data = new T[capacity];
			m_capacity = capacity;
			return;
		}
		T *tmp = new T[capacity];
		for(uint i=0; i<m_size; ++i)
		{
			tmp[i] = m_data[i];
		}
		CH_SFDELARR(m_data);
		m_data = tmp;
	}

	iterator begin()
	{
		CH_ASSERT(m_data);
		return m_data;
	}

	const_iterator const_begin() const
	{
		return begin();
	}

	iterator end()
	{
		CH_ASSERT(m_data);
		return m_data+size();
	}
	const_iterator const_end() const
	{
		return end();
	}

	void push_back(const T &par)
	{
		if(m_data==nullptr)
		{
			reserve(128);
		}

		if(m_size+1 > m_capacity)
		{
			m_capacity = m_capacity<<1;
			this->reserve(m_capacity);
		}
		
		m_data[m_size]=par;
		++m_size;
	}

	T &back() 
	{
		CH_ASSERT(m_size > 0);
		return m_data[m_size-1];
	}

	void pop_back()
	{
		CH_ASSERT(m_size>0);
		m_data[m_size-1]=T();
		--m_size;
	}

	void remove(uint index)
	{
		CH_ASSERT(index<m_size);
		swap(m_data[index],m_data[m_size-1]);
		pop_back();
	}

	void clear() 
	{
		for(iterator itr = begin(); itr!=end(); ++itr)
		{
			*itr=T();
		}
		m_size=0;
	}

private:
	uint m_size;
	uint m_capacity;
	T *m_data;
};
*/

NS_CH_END