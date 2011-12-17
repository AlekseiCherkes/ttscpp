#define GTEST_LINKED_AS_SHARED_LIBRARY 1

//--------------------------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma warning(disable : 4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable : 4275) // non – DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#endif

//--------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//--------------------------------------------------------------------------------------------------