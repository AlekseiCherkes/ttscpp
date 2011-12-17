#include "gtest.hpp"

#include "foundation/string.hpp"
#include "foundation/literal.hpp"
#include "foundation/log.hpp"

//--------------------------------------------------------------------------------------------------

using namespace testing;
using namespace tts::engine;

//--------------------------------------------------------------------------------------------------

class MockWriter : public LogWriter
{
public:
	MOCK_METHOD2(Write, void(LogMessageSeverity severity, const char* message));
};

//--------------------------------------------------------------------------------------------------

class LogTest : public testing::Test
{
public:
	LogTest() :
	  m_ha(),
	  m_log(&m_ha)
	{
		m_log.addWriter(&m_mw);
	}

	~LogTest()
	{
	}

protected:
	HeapAllocator m_ha;
	MockWriter m_mw;
	Log m_log;
};

//--------------------------------------------------------------------------------------------------

TEST_F(LogTest, Simple1)
{
	EXPECT_CALL(m_mw, Write(INF, StrEq("test")));
	m_log.inf() << "test";
}

TEST_F(LogTest, Simple2)
{
	EXPECT_CALL(m_mw, Write(WRN, StrEq("test")));
	m_log.wrn() << "test";
}

TEST_F(LogTest, Simple3)
{
	EXPECT_CALL(m_mw, Write(ERR, StrEq("test")));
	m_log.err() << "test";
}

TEST_F(LogTest, SimpleRus)
{
	EXPECT_CALL(m_mw, Write(ERR, StrEq(RUS_EM RUS_A RUS_EM RUS_A)));
	m_log.err() << RUS_EM RUS_A RUS_EM RUS_A;
}

//--------------------------------------------------------------------------------------------------

#define LOG_TEST(NAME, TYPE, STR, VALUE)			\
	TEST_F(LogTest, NAME)							\
	{												\
		EXPECT_CALL(m_mw, Write(ERR, StrEq(STR)));	\
		TYPE var = VALUE;							\
		m_log.err() << var;							\
	}												\

LOG_TEST(Bool1, bool, "false", false)
LOG_TEST(Bool2, bool, "true", true)
LOG_TEST(Short1, short, "1", 1)
LOG_TEST(Short2, short, "-1", -1)
LOG_TEST(UnsignedShort, unsigned short, "1", 1)
LOG_TEST(Int, int, "1", 1)
LOG_TEST(UnsignedInt, unsigned int, "1", 1)
LOG_TEST(Long, long, "1", 1)
LOG_TEST(UnsignedLong, unsigned long, "1", 1)
LOG_TEST(Float, float, "1.00", 1.0f)
LOG_TEST(Double, double, "1.00", 1.0)
LOG_TEST(LongDouble, long double, "1.00", 1.0)
//LOG_TEST(Pointer1, const void*, "00000000", NULL)
//LOG_TEST(Pointer2, const void*, "ff123456", (void*) 0xff123456)
LOG_TEST(Char, char, "t", 't')
LOG_TEST(SignedChar, signed char, "t", 't')
LOG_TEST(UnsignedChar, unsigned char, "t", 't')
LOG_TEST(ConstCharPtr, const char*, "test", "test")
LOG_TEST(ConstCharPtrRus, const char*, RUS_EM RUS_A RUS_EM RUS_A, RUS_EM RUS_A RUS_EM RUS_A)


//-- TODO: разобраться
//LOG_TEST(ConstSignedCharPtr, const signed char*, "test", "test");
//LOG_TEST(ConstUnsignedCharPtr, const unsigned char*, "test", "test");

//--------------------------------------------------------------------------------------------------
