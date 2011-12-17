#ifndef LOG_HPP
#define LOG_HPP

//-------------------------------------------------------------------------------------------------

#include "engine.hpp"
#include "memory.hpp"

#include <vector>
#include <sstream>

//-------------------------------------------------------------------------------------------------

namespace tts { namespace engine {

//-------------------------------------------------------------------------------------------------

enum LogMessageSeverity
{
    INF = 0,
    WRN = 1,
    ERR = 2,
    ALL = INF | WRN | ERR
};

//-------------------------------------------------------------------------------------------------
//-- LogWriter
//-------------------------------------------------------------------------------------------------

class LogWriter
{
public:
	LogWriter();
	virtual ~LogWriter();

    virtual void Write(LogMessageSeverity severity, const char* message) = 0;
};


//-------------------------------------------------------------------------------------------------
//-- Log
//-------------------------------------------------------------------------------------------------

class Log
{
public:
	Log(Allocator* allocator);
	~Log();

    void addWriter(LogWriter* writer);
    void remWriter(LogWriter* writer);

    void write(LogMessageSeverity severity, const char* message);

    class LogStream
    {
    public:
        LogStream(Log* log, LogMessageSeverity severity, Allocator* allocator);
        ~LogStream();

        LogStream& operator << (const std::string& str);

        LogStream& operator << (bool val);
        LogStream& operator << (short val);
        LogStream& operator << (unsigned short val);
        LogStream& operator << (int val);
        LogStream& operator << (unsigned int val);
        LogStream& operator << (long val);
        LogStream& operator << (unsigned long val);
        LogStream& operator << (float val);
        LogStream& operator << (double val);
        LogStream& operator << (long double val);
        LogStream& operator << (const void* val);

        LogStream& operator << (char c);
        LogStream& operator << (signed char c);
        LogStream& operator << (unsigned char c);
        LogStream& operator << (const char* s);
        //LogStream& operator << (const signed char* s);
        //LogStream& operator << (const unsigned char* s);

    private:
        Log* m_log;
        LogMessageSeverity m_severity;
        Allocator* m_allocator;
    };

    LogStream& inf();
    LogStream& wrn();
    LogStream& err();

private:
	std::vector<LogWriter*, StlAllocator<LogWriter*> > m_writers;

    LogStream m_inf;
    LogStream m_wrn;
    LogStream m_err;
};

//-------------------------------------------------------------------------------------------------
}} // tts::engine

#endif // LOG_HPP