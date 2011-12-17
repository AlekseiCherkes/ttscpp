#ifndef TYPE_HPP
#define TYPE_HPP

//--------------------------------------------------------------------------------------------------

#include "foundation/memory.hpp"

#include <string>
#include <vector>

//--------------------------------------------------------------------------------------------------

namespace tts { namespace engine {

//--------------------------------------------------------------------------------------------------

typedef std::string<char, std::char_traits<char>, StlAllocator<char> > String;

template<typename T>
struct Vector
{
    typedef std::vector<T, StlAllocator<T> > vectorType;
};

//--------------------------------------------------------------------------------------------------
}} // tts::engine

#endif // TYPE_HPP



