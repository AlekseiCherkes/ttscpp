#include "memory.hpp"

#ifdef __APPLE__
#include "malloc/malloc.h"
#endif

#include <memory>
#include <assert.h> //-- TODO: ...

//-------------------------------------------------------------------------------------------------

using namespace tts::engine;

//-------------------------------------------------------------------------------------------------
//-- ProxyAllocator
//-------------------------------------------------------------------------------------------------

ProxyAllocator::ProxyAllocator(const char* name, Allocator* allocator) :
    m_name(name),
    m_allocator(allocator)
{
}

//-------------------------------------------------------------------------------------------------

const char* ProxyAllocator::name()
{
    return m_name;
}

//-------------------------------------------------------------------------------------------------

void* ProxyAllocator::allocate(size_t size)
{
    assert(m_allocator);
    return m_allocator->allocate(size);
}

//-------------------------------------------------------------------------------------------------

void ProxyAllocator::deallocate(void *p)
{
    assert(m_allocator);
    m_allocator->deallocate(p);
}

//-------------------------------------------------------------------------------------------------

size_t ProxyAllocator::allocated_size()
{
    assert(m_allocator);
    return m_allocator->allocated_size();
}

//-------------------------------------------------------------------------------------------------
//-- HeapAllocator
//-------------------------------------------------------------------------------------------------

HeapAllocator::HeapAllocator() : 
	m_size(0)
{
}

//-------------------------------------------------------------------------------------------------

HeapAllocator::~HeapAllocator()
{
	assert(m_size == 0);    //-- TODO: replace by TTS_ASSERT
}

//-------------------------------------------------------------------------------------------------

void* HeapAllocator::allocate(size_t size)
{
	//std::cout<<"Heap alloc: " << m_name << "--" << size << "\n";
#if defined (_MSC_VER)
	m_size += size;
#elif defined (__APPLE__)
    m_size += malloc_good_size(size);
#else
#error "You OS is not supported by HeapAllocator."
#endif
	return malloc(size);
}

//-------------------------------------------------------------------------------------------------

void HeapAllocator::deallocate(void *p)
{        
#if defined (_MSC_VER)
	size_t size = _msize(p);
#elif defined (__APPLE__)
    size_t size = malloc_size(p);
#else
#error "You OS is not supported."
#endif
	m_size -= size;
	//std::cout<<"Heap dealloc: " << m_name << "--" << size << "\n";
	return free(p);
}

//-------------------------------------------------------------------------------------------------

size_t HeapAllocator::allocated_size()
{
	return m_size;
}

//-------------------------------------------------------------------------------------------------




