--------------------------------------------------------------------------------
-- MinGW
--------------------------------------------------------------------------------

1) Запустить mingw-get-inst-20110802.exe
2) Выбрать use pre-packaged repository catalogues (20110802)
3) Оставить дирректорию для установки по умолчанию
	С:\MinGW
4) Выбрать все доступные компоненты кроме Fortran Compiler и ObjC Compiler.
5) Дождаться скачивания необходимых пакутов из интернета и установки их на 
компьютрер.

Использование инсталятора обязательно т.к в этом случае в реестр прописывается 
путь к исполняемым файлам MinGW после чего CMake сможет находить их 
автоматически.

"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\MinGW;InstallLocation]/bin"\
"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\MSYS-1.0_is1;Inno Setup: App Path]/bin"
"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\MinGW;InstallLocation]/bin"

При конфигурировании указывать MSYS, а не MinGW.

--------------------------------------------------------------------------------