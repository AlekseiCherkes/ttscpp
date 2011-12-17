//-- My own version of console test runner based on code from gmock_main.

#define GTEST_LINKED_AS_SHARED_LIBRARY 1

#ifdef _MSC_VER
#pragma warning(disable : 4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable : 4275) // non – DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#endif

#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// MS C++ compiler/linker has a bug on Windows (not on Windows CE), which
// causes a link error when _tmain is defined in a static library and UNICODE
// is enabled. For this reason instead of _tmain, main function is used on
// Windows. See the following link to track the current status of this bug:
// http://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=394464  // NOLINT
#if GTEST_OS_WINDOWS_MOBILE
# include <tchar.h>  // NOLINT
int _tmain(int argc, TCHAR** argv) {
#else
int main(int argc, char** argv) {
#endif  // GTEST_OS_WINDOWS_MOBILE

#ifdef _MSC_VER
	__declspec(dllimport) int PullInMyLibrary();
	static int tmp = PullInMyLibrary();
#endif

	// Since Google Mock depends on Google Test, InitGoogleMock() is
	// also responsible for initializing Google Test.  Therefore there's
	// no need for calling testing::InitGoogleTest() separately.
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}

