# TODO: move this code to the parent folder to appear in the IDE
# TODO: document this file
# TODO: write versions of all used libs
###############################################################################
# pugixml
###############################################################################
# use original CMakeList.txt file.

add_subdirectory(${CMAKE_SOURCE_DIR}/third/pugixml/scripts)
include_directories(${CMAKE_SOURCE_DIR}/third/pugixml/src)

###############################################################################
# gmock with gtest
###############################################################################
# use original CMakeList.txt file.

# We should build gtest as shared lib if the test lib is shared
# TODO: restore prev. value correctly
SET(BUILD_SHARED_LIBS ON)
add_subdirectory(${CMAKE_SOURCE_DIR}/third/gmock)
SET(BUILD_SHARED_LIBS OFF)

###############################################################################
# pcre
###############################################################################
# use original CMakeList.txt file.

# TODO: remove install commands from pcre CMake script.

SET(PCRE_SUPPORT_UTF8 ON CACHE BOOL
    "Enable support for the Unicode UTF-8 encoding.")

SET(PCRE_SUPPORT_UNICODE_PROPERTIES ON CACHE BOOL
    "Enable support for Unicode properties. (If set, UTF-8 support will be enabled as well)")

OPTION(PCRE_BUILD_PCREGREP "Build pcregrep" OFF)
OPTION(PCRE_BUILD_TESTS    "Build the tests" OFF)

add_subdirectory(${CMAKE_SOURCE_DIR}/third/pcre)

###############################################################################
# utf8
###############################################################################
# header only library

# add_library(utf8cpp utf8/source/utf8.h 
#					utf8/source/utf8/checked.h 
#					utf8/source/utf8/unchecked.h 
#					utf8/source/utf8/core.h)

###############################################################################
# zlib (zlib-1.2.5)
###############################################################################
# I wrote my own CMakeList.txt

# Remarks:
#    1) Использую дефолтный zconf.h т.к переменные устанавливаемые туда через 
#       CMake на самом деле не используютя в коде.

set(ZLIB_PUBLIC_HDRS
    zlib/zconf.h
    zlib/zlib.h
)

set(ZLIB_PRIVATE_HDRS
    zlib/crc32.h
    zlib/deflate.h
    zlib/gzguts.h
    zlib/inffast.h
    zlib/inffixed.h
    zlib/inflate.h
    zlib/inftrees.h
    zlib/trees.h
    zlib/zutil.h
)

set(ZLIB_SRCS
    zlib/adler32.c
    zlib/compress.c
    zlib/crc32.c
    zlib/deflate.c
    zlib/gzclose.c
    zlib/gzlib.c
    zlib/gzread.c
    zlib/gzwrite.c
    zlib/inflate.c
    zlib/infback.c
    zlib/inftrees.c
    zlib/inffast.c
    zlib/trees.c
    zlib/uncompr.c
    zlib/zutil.c
    zlib/win32/zlib1.rc
)

set(MINIZIP_PUBLIC_HDRS
    zlib/contrib/minizip/crypt.h
    zlib/contrib/minizip/ioapi.h
    zlib/contrib/minizip/iowin32.h
    zlib/contrib/minizip/mztools.h
    zlib/contrib/minizip/unzip.h
    zlib/contrib/minizip/zip.h
)

set(MINIZIP_SRCS
    zlib/contrib/minizip/ioapi.c
    zlib/contrib/minizip/iowin32.c
    zlib/contrib/minizip/mztools.c
    zlib/contrib/minizip/unzip.c
    zlib/contrib/minizip/zip.c
)

include_directories(zlib zlib/contrib/minizip)

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
endif()

add_library(zlib ${ZLIB_PUBLIC_HDRS} ${ZLIB_PRIVATE_HDRS} ${ZLIB_SRCS})
add_library(minizip ${MINIZIP_PUBLIC_HDRS} ${MINIZIP_PRIVATE_HDRS} ${MINIZIP_SRCS})

###############################################################################
# Third party folder in generated solutions
###############################################################################

set_target_properties(gtest gtest_main gmock gmock_main
                      pugixml pcre pcrecpp pcreposix zlib minizip
                      PROPERTIES FOLDER Third)

###############################################################################
# End
###############################################################################