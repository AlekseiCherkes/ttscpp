cmake_minimum_required(VERSION 2.8)

###############################################################################
# Project
###############################################################################

project(TTS)

###############################################################################
# Common utils
###############################################################################

#-- find all source and header files in subdirectories
#-- and arrange them into source groups according directory structure.

macro(COLLECT_ALL_SOURCES directory files)
	file(GLOB_RECURSE globbed RELATIVE ${CMAKE_SOURCE_DIR}/${directory}/ *.cpp *.hpp)
	set(${files} ${globbed})
	foreach(file ${globbed})
		get_filename_component(dir ${file} PATH)
		if(dir)
			string(REPLACE "/" "\\" dir ${dir})
			source_group(${dir} FILES ${file})
		else()
			source_group("" FILES ${file})
		endif()
	endforeach()
endmacro()

###############################################################################
# Global vars
###############################################################################

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

###############################################################################
# Main projects
###############################################################################

add_subdirectory(third)

# TODO: ...
IF(MSVC)
	#ADD_DEFINITIONS(/W4)
ELSEIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
ENDIF()


add_subdirectory(admin)
add_subdirectory(android_demo)
add_subdirectory(android_test_runner)
add_subdirectory(console_demo)
add_subdirectory(console_test_runner)
add_subdirectory(engine)
add_subdirectory(test)

###############################################################################
# Documentation
###############################################################################

# Add a target to generate API documentation with Doxygen
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    CONFIGURE_FILE(
        ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in 
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    ADD_CUSTOM_TARGET(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM)
ENDIF(DOXYGEN_FOUND)

###############################################################################
# Build console file
###############################################################################

#IF(ANDROID OR MINGW)
#	CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/build.bat.cmake 
#				   ${CMAKE_BINARY_DIR}/build.bat)
#ENDIF(ANDROID OR MINGW)

###############################################################################
# End
###############################################################################