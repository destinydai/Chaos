#pragma once


NS_CH_BEG

template<typename T>
class ObjectTraits_ 
{
public : 
	//    convert an ObjectTraits<T> to ObjectTraits<U>
	template<typename U>
	struct rebind 
	{
		typedef ObjectTraits_<U> other;
	};

public : 
	inline explicit ObjectTraits_() {}
	inline ~ObjectTraits_() {}
	template <typename U>
	inline explicit ObjectTraits_(ObjectTraits_<U> const&) {}

	//    address
	inline T* address(T& r) { return &r; }
	inline T const* address(T const& r) { return &r; }

	inline void construct(T* p, const T& t) { new(p) T(t); }
	inline void destroy(T* p) { p->~T(); }
};    //    end of class ObjectTraits



template<typename T>
class StandardAllocPolicy_ 
{
public : 
	//    typedefs
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

public : 
	//    convert an StandardAllocPolicy<T> to StandardAllocPolicy<U>
	template<typename U>
	struct rebind 
	{
		typedef StandardAllocPolicy_<U> other;
	};

public : 
	inline explicit StandardAllocPolicy_() 
	{

	}
	inline ~StandardAllocPolicy_() 
	{

	}
	inline explicit StandardAllocPolicy_(StandardAllocPolicy_  const&obj) 
	{

	}
	template <typename U>
	inline explicit StandardAllocPolicy_(StandardAllocPolicy_<U> const &obj) 
	{

	}

	//    memory allocation
	inline pointer allocate(size_type cnt, typename std::allocator<void>::const_pointer = 0) 
	{ 
		T *p = reinterpret_cast<pointer>(::operator new(cnt*sizeof(T))); 
		return p;
	}
	inline void deallocate(pointer p, size_type) 
	{ 
		::operator delete(p); 
	}

	//    size
	inline size_type max_size() const 
	{ 
		return 0xffffff00;//std::numeric_limits<size_type>::max(); 
	}
};    //    end of class StandardAllocPolicy

// determines if memory from another
// allocator can be deallocated from this one
template<typename T, typename T2>
inline bool operator==(StandardAllocPolicy_<T> const&, StandardAllocPolicy_<T2> const&) 
{ 
		return true;
}
template<typename T, typename OtherAllocator>
inline bool operator==(StandardAllocPolicy_<T> const&, OtherAllocator const&) 
{ 
		return false; 
}

template<typename T, typename Policy = StandardAllocPolicy_<T>, typename Traits = ObjectTraits_<T> >
class Allocator : public Policy, public Traits 
{
private : 
	typedef Policy AllocationPolicy;
	typedef Traits TTraits;

public : 
	typedef typename AllocationPolicy::size_type size_type;
	typedef typename AllocationPolicy::difference_type difference_type;
	typedef typename AllocationPolicy::pointer pointer;
	typedef typename AllocationPolicy::const_pointer const_pointer;
	typedef typename AllocationPolicy::reference reference;
	typedef typename AllocationPolicy::const_reference const_reference;
	typedef typename AllocationPolicy::value_type value_type;

public : 
	template<typename U>
	struct rebind 
	{
		typedef Allocator<U, typename AllocationPolicy::rebind<U>::other,typename TTraits::rebind<U>::other > other;
	};

public : 
	inline explicit Allocator() {}

	inline ~Allocator() {}

	inline Allocator(Allocator const& rhs):Traits(rhs), Policy(rhs) {}

	template <typename U>
	inline Allocator(Allocator<U> const&) {}

	template <typename U, typename P, typename T2>
	inline Allocator(Allocator<U, P, T2> const& rhs):Traits(rhs), Policy(rhs) {}
};    //    end of class Allocator

// determines if memory from another
// allocator can be deallocated from this one
template<typename T, typename P, typename Tr>
inline bool operator==(Allocator<T, P, Tr> const& lhs, Allocator<T, P, Tr> const& rhs) 
{ 
		return operator==(static_cast<P&>(lhs), static_cast<P&>(rhs)); 
}
template<typename T, typename P, typename Tr, typename T2, typename P2, typename Tr2>
inline bool operator==(Allocator<T, P, Tr> const& lhs, Allocator<T2, P2, Tr2> const& rhs) 
{ 
		return operator==(static_cast<P&>(lhs), static_cast<P2&>(rhs)); 
}
template<typename T, typename P, typename Tr, typename OtherAllocator>
inline bool operator==(Allocator<T, P, Tr> const& lhs, OtherAllocator const& rhs) 
{ 
		return operator==(static_cast<P&>(lhs), rhs); 
}
template<typename T, typename P, typename Tr>
inline bool operator!=(Allocator<T, P, Tr> const& lhs, Allocator<T, P, Tr> const& rhs) 
{ 
		return !operator==(lhs, rhs); 
}
template<typename T, typename P, typename Tr, typename T2, typename P2, typename Tr2>
inline bool operator!=(Allocator<T, P, Tr> const& lhs, Allocator<T2, P2, Tr2> const& rhs) 
{
		return !operator==(lhs, rhs); 
}
template<typename T, typename P, typename Tr, typename OtherAllocator>
inline bool operator!=(Allocator<T, P, Tr> const& lhs, OtherAllocator const& rhs) 
{
		return !operator==(lhs, rhs); 
}



NS_CH_END
