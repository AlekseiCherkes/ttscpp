#ifndef MEMORY_HPP
#define MEMORY_HPP

//-------------------------------------------------------------------------------------------------

#include <cstddef>
#include <limits>

//-------------------------------------------------------------------------------------------------

namespace tts { namespace engine {

//-------------------------------------------------------------------------------------------------
//-- Allocator
//--
//-- Abstract base class for all memory allocators
//-------------------------------------------------------------------------------------------------

class Allocator
{
public:
	virtual ~Allocator()
	{
	}

    virtual void *allocate(size_t size) = 0;
    virtual void deallocate(void *p) = 0;
    virtual size_t allocated_size() = 0;

	template <class T, class P> 
    T* make_new(const P& p1) 
	{
		return new (allocate(sizeof(T))) T(p1);
	}
 
    template <class T> 
    void make_delete(T *p) 
	{
        if (p) 
		{
            p->~T();
            deallocate(p);
        }
    }
};

//-------------------------------------------------------------------------------------------------
//-- ProxyAllocator
//-------------------------------------------------------------------------------------------------

class ProxyAllocator : public Allocator
{
public:
    ProxyAllocator(const char* name, Allocator* allocator);

    const char* name();

    virtual void* allocate(size_t size);
    virtual void deallocate(void *p);
    virtual size_t allocated_size();

private:
    const char* m_name;
    Allocator* m_allocator;
};

//-------------------------------------------------------------------------------------------------
//-- HeapAllocator
//--
//-- Allocator for allocate dynamic memory on the heap
//-------------------------------------------------------------------------------------------------

class HeapAllocator : public Allocator
{
public:
	HeapAllocator();
	virtual ~HeapAllocator();

    virtual void* allocate(size_t size);
    virtual void deallocate(void *p);
    virtual size_t allocated_size();

private:
	HeapAllocator(const HeapAllocator&);
	HeapAllocator& operator = (const HeapAllocator&);

	size_t m_size;
};

//-------------------------------------------------------------------------------------------------
//-- StlAllocator
//--
//-- Implementation of the std::allocator policy through our Allocator interface
//-------------------------------------------------------------------------------------------------

template<typename T>
class StlAllocator 
{
public: 
    //-- typedefs

    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public: 
    //-- convert an allocator<T> to allocator<U>

    template<typename U>
    struct rebind 
	{
        typedef StlAllocator<U> other;
    };

public:    
    inline StlAllocator(Allocator* allocator) 
		: m_allocator(allocator) 
	{
	}

    inline ~StlAllocator() 
	{
		m_allocator = NULL;
	}

    inline StlAllocator(StlAllocator const& other) 
	{
		m_allocator = other.m_allocator;
	}

    template<typename U>
    inline StlAllocator(StlAllocator<U> const& other) 
	{
		m_allocator = other.m_allocator;
	}

    //-- address

    inline pointer address(reference r) 
	{ 
		return &r; 
	}

    inline const_pointer address(const_reference r) 
	{ 
		return &r; 
	}

    //-- memory allocation

    pointer allocate(size_type cnt, const_pointer = 0) 
	{ 
		return reinterpret_cast<pointer> (m_allocator->allocate(cnt * sizeof(T)));
    }

    void deallocate(pointer p, size_type) 
	{ 
        m_allocator->deallocate(p);
    }

    //-- size

    inline size_type max_size() const 
	{ 
        return std::numeric_limits<size_type>::max() / sizeof(T);
	}

    //-- construction/destruction

    inline void construct(pointer p, const T& t) 
	{ 
		new(p) T(t); 
	}

    inline void destroy(pointer p) 
	{ 
		p->~T();
	}

	//-- operators

    inline bool operator == (StlAllocator const& other) 
	{
		return m_allocator == other.m_allocator; 
	}

    inline bool operator != (StlAllocator const& a) 
	{ 
		return ! operator==(a); 
	}

	Allocator* m_allocator; // should be public for StlAllocator(StlAllocator<U> const& other) 
};

//-------------------------------------------------------------------------------------------------

template <class T1, class T2>
bool operator == (const StlAllocator<T1>& op1, const StlAllocator<T2>& op2) throw()
{
    return op1.m_allocator == op2.m_allocator;
}

//-------------------------------------------------------------------------------------------------

template <class T1, class T2>
bool operator != (const StlAllocator<T1>& op1, const StlAllocator<T2>& op2) throw()
{
    return op1.m_allocator != op2.m_allocator;
}

//-------------------------------------------------------------------------------------------------

}} // tts::engine

#endif // MEMORY_HPP