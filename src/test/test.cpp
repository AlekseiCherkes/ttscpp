#include "gtest.hpp"

//--------------------------------------------------------------------------------------------------

using namespace testing;

//--------------------------------------------------------------------------------------------------

TEST(GTest, Test1) 
{
	EXPECT_LE(2, 2);
}

//--------------------------------------------------------------------------------------------------

class MockTurtle 
{
public:
	MOCK_METHOD0(PenUp, void());
	MOCK_METHOD0(PenDown, void());
	MOCK_METHOD1(Forward, void(int distance));
	MOCK_METHOD1(Turn, void(int degrees));
	MOCK_METHOD2(GoTo, void(int x, int y));
	MOCK_CONST_METHOD0(GetX, int());
	MOCK_CONST_METHOD0(GetY, int());
};

TEST(GMock, Test1)
{
	MockTurtle t;

	EXPECT_CALL(t, Forward(_)).Times(AnyNumber());
	EXPECT_CALL(t, Forward(1)).Times(2).RetiresOnSaturation();

	{
		t.Forward(1);
		t.Forward(0);
		t.Forward(1);
		t.Forward(0);
		t.Forward(0);
	}
}

//--------------------------------------------------------------------------------------------------