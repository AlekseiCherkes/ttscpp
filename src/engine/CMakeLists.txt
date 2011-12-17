include_directories(${CMAKE_SOURCE_DIR}/third/pcre)
include_directories(${CMAKE_BINARY_DIR}/third/pcre)

include_directories(${CMAKE_SOURCE_DIR}/engine/)

COLLECT_ALL_SOURCES(engine files)
add_library (engine ${files})
target_link_libraries(engine pcre pcrecpp)

# Некоторые заментки по инсталяции сторонних пакетов под Windows:
#    1) Qt. 
#       Скачивать нужно не полностью SDK, а так называемые qt libraries.
#       Прописывается в реестр. корректно работает с разными версиями.
#       СMake находит установленную версию автоматически. Для тех, кто любит, нестандартную 
#       инсталяцию есть переменная QT_QMAKE_EXECUTABLE.
#
#    2) DoxyGen. Стандартный инсталятор ставит его в ProgramFiles и прописывает системный Path 
#       к нему. CMake находит все автоматически.
        