IF(NOT ANDROID)
	include_directories(${CMAKE_SOURCE_DIR}/third/gmock/include)
	include_directories(${CMAKE_SOURCE_DIR}/third/gmock/gtest/include)
	add_executable(console_test_runner main.cpp)
	target_link_libraries(console_test_runner test)
ENDIF(NOT ANDROID)