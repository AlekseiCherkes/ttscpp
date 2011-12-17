#include "utf8.h"
#include <vector>
#include <iterator>

#include "gtest.hpp"

using namespace utf8;
using namespace std;

//--------------------------------------------------------------------------------------------------

TEST(UTF8, Base)
{
	EXPECT_EQ(1, sizeof(utf8::uint8_t));
	EXPECT_EQ(2, sizeof(utf8::uint16_t));
	EXPECT_EQ(4, sizeof(utf8::uint32_t));
}

//--------------------------------------------------------------------------------------------------

TEST(UTF8, Iterator)
{
	char* threechars = "\xf0\x90\x8d\x86\xe6\x97\xa5\xd1\x88";
	utf8::iterator<char*> it(threechars, threechars, threechars + 9);
	utf8::iterator<char*> it2 = it;
	EXPECT_TRUE (it2 == it);
	EXPECT_TRUE (*it == 0x10346);
	EXPECT_TRUE (*(++it) == 0x65e5);
	EXPECT_TRUE ((*it++) == 0x65e5);
	EXPECT_TRUE (*it == 0x0448);
	EXPECT_TRUE (it != it2);
	utf8::iterator<char*> endit (threechars + 9, threechars, threechars + 9);  
	EXPECT_TRUE (++it == endit);
	EXPECT_TRUE (*(--it) == 0x0448);
	EXPECT_TRUE ((*it--) == 0x0448);
	EXPECT_TRUE (*it == 0x65e5);
	EXPECT_TRUE (--it == utf8::iterator<char*>(threechars, threechars, threechars + 9));
	EXPECT_TRUE (*it == 0x10346);
}

//--------------------------------------------------------------------------------------------------
//-- I have borrowed this tests from:
//-- http://www.codeproject.com/script/Articles/ViewDownloads.aspx?aid=14637

TEST(UTF8, Main)
{
	//append
    unsigned char u[5] = {0,0,0,0,0};

    unsigned char* end = append(0x0448, u);
	EXPECT_TRUE (u[0] == 0xd1 && u[1] == 0x88 && u[2] == 0 && u[3] == 0 && u[4] == 0);

    end = append(0x65e5, u);
	EXPECT_TRUE (u[0] == 0xe6 && u[1] == 0x97 && u[2] == 0xa5 && u[3] == 0 && u[4] == 0);

    end = append(0x10346, u);
	EXPECT_TRUE (u[0] == 0xf0 && u[1] == 0x90 && u[2] == 0x8d && u[3] == 0x86 && u[4] == 0);

    //next
    unsigned char twochars[] = {0xE6, 0x97, 0xA5, 0xd1, 0x88, 0x0};
	unsigned char* w = twochars;
	int cp = next(w, twochars + 6);
	EXPECT_TRUE (cp == 0x65e5);
	EXPECT_TRUE (w == twochars + 3);

    //previous
    cp = previous (w, twochars - 1);
	EXPECT_TRUE (cp == 0x65e5);
	EXPECT_TRUE (w == twochars);

    // advance
    w = twochars;
	advance (w, 2, twochars + 6);
	EXPECT_TRUE (w == twochars + 5);

    // distance
    size_t dist = utf8::distance(twochars, twochars + 5);
	EXPECT_TRUE (dist == 2);

    // utf32to8
    int utf32string[] = {0x448, 0x65E5, 0x10346, 0};
	vector<unsigned char> utf8result;
	utf32to8(utf32string, utf32string + 3, back_inserter(utf8result));
	EXPECT_TRUE (utf8result.size() == 9);

    //utf8to32
    vector<int> utf32result;
	utf8to32(twochars, twochars + 5, back_inserter(utf32result));
	EXPECT_TRUE (utf32result.size() == 2);

    //utf16to8
    unsigned short utf16string[] = {0x41, 0x0448, 0x65e5, 0xd834, 0xdd1e};
	utf8result.clear();
	utf16to8(utf16string, utf16string + 5, back_inserter(utf8result));
	EXPECT_TRUE (utf8result.size() == 10);

    //utf8to16
    unsigned char utf8_with_surrogates[] = {0xE6, 0x97, 0xA5, 0xd1, 0x88, 0xf0, 0x9d, 0x84, 0x9e};
	vector <unsigned short> utf16result;
	utf8to16(utf8_with_surrogates, utf8_with_surrogates + 9, back_inserter(utf16result));
	EXPECT_TRUE (utf16result.size() == 4);
	EXPECT_TRUE (utf16result[2] == 0xd834);
	EXPECT_TRUE (utf16result[3] == 0xdd1e);

    //find_invalid
    unsigned char utf_invalid[] = {0xE6, 0x97, 0xA5, 0xd1, 0x88, 0xfa};
	unsigned char* invalid = find_invalid(utf_invalid, utf_invalid + 6);
	EXPECT_TRUE (invalid == utf_invalid + 5);

	//is_valid
	bool bvalid = is_valid(utf_invalid, utf_invalid + 6);
	EXPECT_TRUE (bvalid == false);
	bvalid = is_valid(utf8_with_surrogates, utf8_with_surrogates + 9);
	EXPECT_TRUE (bvalid == true);

	//is_bom
	unsigned char byte_order_mark[] = {0xef, 0xbb, 0xbf};
	bool bbom = is_bom(byte_order_mark);
	EXPECT_TRUE (bbom == true);

   //////////////////////////////////////////////////////////
   //// Unchecked variants
   //////////////////////////////////////////////////////////

	//append
	memset(u, 0, 5);
	end = unchecked::append(0x0448, u);
	EXPECT_TRUE (u[0] == 0xd1 && u[1] == 0x88 && u[2] == 0 && u[3] == 0 && u[4] == 0);

	end = unchecked::append(0x65e5, u);
	EXPECT_TRUE (u[0] == 0xe6 && u[1] == 0x97 && u[2] == 0xa5 && u[3] == 0 && u[4] == 0);

	end = unchecked::append(0x10346, u);
	EXPECT_TRUE (u[0] == 0xf0 && u[1] == 0x90 && u[2] == 0x8d && u[3] == 0x86 && u[4] == 0);

	//next
	w = twochars;
	cp = unchecked::next(w);
	EXPECT_TRUE (cp == 0x65e5);
	EXPECT_TRUE (w == twochars + 3);

	//previous
	cp = unchecked::previous (w);
	EXPECT_TRUE (cp == 0x65e5);
	EXPECT_TRUE (w == twochars);

	// advance
	w = twochars;
	unchecked::advance (w, 2);
	EXPECT_TRUE (w == twochars + 5);

	// distance
	dist = unchecked::distance(twochars, twochars + 5);
	EXPECT_TRUE (dist == 2);

	// utf32to8
	utf8result.clear();
	unchecked::utf32to8(utf32string, utf32string + 3, back_inserter(utf8result));
	EXPECT_TRUE (utf8result.size() == 9);

	//utf8to32
	utf32result.clear();
	unchecked::utf8to32(twochars, twochars + 5, back_inserter(utf32result));
	EXPECT_TRUE (utf32result.size() == 2);

	//utf16to8
	utf8result.clear();
	unchecked::utf16to8(utf16string, utf16string + 5, back_inserter(utf8result));
	EXPECT_TRUE (utf8result.size() == 10);

	//utf8to16
	utf16result.clear();
	unchecked::utf8to16(utf8_with_surrogates, utf8_with_surrogates + 9, back_inserter(utf16result));
	EXPECT_TRUE (utf16result.size() == 4);
	EXPECT_TRUE (utf16result[2] == 0xd834);
	EXPECT_TRUE (utf16result[3] == 0xdd1e);
}

//--------------------------------------------------------------------------------------------------