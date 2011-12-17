#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <locale>

#include <engine.hpp>

#ifdef WIN32
#include <windows.h>
#endif

int
main()
{
	//const char* old_locale = setlocale(LC_ALL, "C.UTF-8");
	//if(!old_locale)
	//{
	//	printf("setlocale - error\n");
	//	return 1;
	//}

 //   _setmode(_fileno(stdout), _O_U16TEXT);
    //_setmode(_fileno(stdout), _O_U8TEXT);
   // _setmode(_fileno(stderr), _O_U8TEXT);

#ifdef WIN32
    //if(!SetConsoleOutputCP(65001) ||
    //   !SetConsoleCP(65001))
    //{
    //    printf("set console code page error.");
    //}
#endif

	//const char* str = RUS_A;

    std::locale::global(std::locale(""));

 //   printf("");

	//printf(str);
 //   printf("\n");
 //   printf("abc");
	//printf("\n");

	////printf(RUS_EM RUS_A RUS_EM RUS_A "\n");
	//wprintf(L"\n");

	//std::wcout<<L"HWфывафыав!";

    //_setmode(_fileno(stdout), _O_U16TEXT);
    //wprintf(L"\x043a\x043e\x0448\x043a\x0430 \x65e5\x672c\x56fd\n");

    //MultiByteToWideChar(CP_UTF8, 0, pInput, -1, pOutput, nLen);
    //MultiByteToWideChar(

    //wprintf(L"мама");
    //printf(RUS_EM RUS_A RUS_EM RUS_A);

    return 0;
}
