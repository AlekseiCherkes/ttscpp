#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_WARNINGS
#endif

#include "log.hpp"

#include <stdio.h>
#include <algorithm>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif 

//--------------------------------------------------------------------------------------------------

using namespace tts::engine;

//--------------------------------------------------------------------------------------------------
// Log
//--------------------------------------------------------------------------------------------------

LogWriter::LogWriter()
{
}

LogWriter::~LogWriter()
{
}

//--------------------------------------------------------------------------------------------------
// Log
//--------------------------------------------------------------------------------------------------

// TODO: reconsider

#ifdef _MSC_VER
#pragma  warning(disable : 4355) // 'this' : used in base member initializer list
#endif 

Log::Log(Allocator* allocator) :
	m_writers(StlAllocator<LogWriter*>(allocator)),
    m_inf(this, INF, allocator),
    m_wrn(this, WRN, allocator),
    m_err(this, ERR, allocator)
{
}

#ifdef _MSC_VER
#pragma  warning(default : 4355)
#endif 

//--------------------------------------------------------------------------------------------------

Log::~Log()
{
}

//--------------------------------------------------------------------------------------------------

void Log::addWriter(LogWriter* writer)
{
	m_writers.push_back(writer);
}

//--------------------------------------------------------------------------------------------------

void Log::remWriter(LogWriter* writer)
{
	std::vector<LogWriter*, StlAllocator<LogWriter*> >::iterator i;
	i = std::find(m_writers.begin(), m_writers.end(), writer);
	if(i != m_writers.end())
	{
		m_writers.erase(i);
	}
}

void Log::write(LogMessageSeverity severity, const char* message)
{
    for(size_t i = 0; i < m_writers.size(); ++i)
    {
        m_writers[i]->Write(severity, message);
    }
}

Log::LogStream& Log::inf()
{
    return m_inf;
}

Log::LogStream& Log::wrn()
{
    return m_wrn;
}

Log::LogStream& Log::err()
{
    return m_err;
}

//--------------------------------------------------------------------------------------------------
// LogStream
//--------------------------------------------------------------------------------------------------

Log::LogStream::LogStream(Log* log, LogMessageSeverity severity, Allocator* allocator) :
    m_log(log),
    m_severity(severity),
    m_allocator(allocator)
{
}

Log::LogStream::~LogStream()
{
}

//--------------------------------------------------------------------------------------------------

#define BUF_SIZE 1024

#define LOG_FUNCTION(TYPE, FORMAT)							\
	Log::LogStream& Log::LogStream::operator << (TYPE val)	\
{															\
	char buf[BUF_SIZE];										\
	snprintf(buf, BUF_SIZE, FORMAT, val);					\
	m_log->write(m_severity, buf);							\
	return *this;											\
}

//--------------------------------------------------------------------------------------------------

Log::LogStream& Log::LogStream::operator << (const std::string& str)
{
    m_log->write(m_severity, str.c_str());
    return *this;
}

Log::LogStream& Log::LogStream::operator << (bool val)
{
	if(val)
	{
		m_log->write(m_severity, "true");
	}
	else
	{
		m_log->write(m_severity, "false");
	}
    return *this;
}

LOG_FUNCTION(short, "%hi")
LOG_FUNCTION(unsigned short, "%hu")

LOG_FUNCTION(int, "%i")
LOG_FUNCTION(unsigned int, "%u")
LOG_FUNCTION(long, "%li")
LOG_FUNCTION(unsigned long, "%lu")
LOG_FUNCTION(float, "%.2f")
LOG_FUNCTION(double, "%.2f")              // TODO: ???
LOG_FUNCTION(long double, "%.2Lf")
LOG_FUNCTION(const void*, "%p")

LOG_FUNCTION(char, "%c")
LOG_FUNCTION(signed char, "%c")
LOG_FUNCTION(unsigned char, "%c")

Log::LogStream& Log::LogStream::operator << (const char* s)
{
    m_log->write(m_severity, s);
    return *this;
}

//LOG_FUNCTION(const signed char*, "%s")   // TODO: ???
//LOG_FUNCTION(const unsigned char*, "%S") // TODO: ???

//--------------------------------------------------------------------------------------------------
