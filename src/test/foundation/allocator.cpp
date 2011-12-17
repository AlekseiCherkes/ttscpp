
//-- TODO: write tests for memory allocation classes and enchace the 
//--       framework for memory leak detection for every test.

//#include <crtdbg.h>
//struct CrtCheckMemory
//{
//  _CrtMemState state1;
//  _CrtMemState state2;
//  _crtMemState state3;
//  CrtCheckMemory()
//  {
//    _CrtMemCheckpoint(&state1);
//  }
//  ~CrtCheckMemory()
//  {
//    _CrtMemCheckpoint(&state2);
//    // using google test you can just do this.
//    EXPECT_EQ(0,_CrtMemDifference( &state3, &state1, &state2));
//    // else just do this to dump the leaked blocks to stdout.
//    if( _CrtMemDifference( &state3, &state1, &state2) )
//      _CrtMemDumpStatistics( &state3 );
//  }
//};