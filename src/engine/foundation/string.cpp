#include "string.hpp"

//------------------------------------------------------------------------------

namespace tts
{
namespace foundation
{

//------------------------------------------------------------------------------

string::string() :
    m_data()
{
}

string::~string()
{
}

string::string(const tts::foundation::string &other) :
    m_data(other.m_data)
{
}

//------------------------------------------------------------------------------

} // namespace tts
} // namespace foundation