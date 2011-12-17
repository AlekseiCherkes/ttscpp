#ifndef STRING_HPP
#define STRING_HPP

//-------------------------------------------------------------------------------------------------

#include <string>

//-------------------------------------------------------------------------------------------------

namespace tts { namespace foundation {

//-------------------------------------------------------------------------------------------------

typedef int char_t;

//-------------------------------------------------------------------------------------------------

class string
{
public:
    string();
    ~string();

    string(const string& other);
    string(const char* str);

    string& operator = (const string& other);

    string to_lower() const; //-- TODO: ...
    string to_upper() const; //-- TODO: ...

private:
    std::string m_data;
};

//-------------------------------------------------------------------------------------------------
}} // tts::engine

#endif // STRING_HPP