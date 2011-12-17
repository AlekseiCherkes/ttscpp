#include "gtest.hpp"

#define PCRE_STATIC
#include "pcrecpp.h"

//--------------------------------------------------------------------------------------------------

using namespace pcrecpp;

//--------------------------------------------------------------------------------------------------

TEST(PCRE, Main)
{
	const char* pattern = "abc*";
	const char* data1 = "abcccccccccc";
	const char* data2 = "abcg";

	RE re(pattern, UTF8());

	EXPECT_TRUE(re.FullMatch(data1));
	EXPECT_FALSE(re.FullMatch(data2));
}

//--------------------------------------------------------------------------------------------------