include_directories(${CMAKE_SOURCE_DIR}/third/pcre)
include_directories(${CMAKE_BINARY_DIR}/third/pcre)

include_directories(${CMAKE_SOURCE_DIR}/engine/)

COLLECT_ALL_SOURCES(engine files)
add_library (engine ${files})
target_link_libraries(engine pcre pcrecpp)

# ��������� �������� �� ���������� ��������� ������� ��� Windows:
#    1) Qt. 
#       ��������� ����� �� ��������� SDK, � ��� ���������� qt libraries.
#       ������������� � ������. ��������� �������� � ������� ��������.
#       �Make ������� ������������� ������ �������������. ��� ���, ��� �����, ������������� 
#       ���������� ���� ���������� QT_QMAKE_EXECUTABLE.
#
#    2) DoxyGen. ����������� ���������� ������ ��� � ProgramFiles � ����������� ��������� Path 
#       � ����. CMake ������� ��� �������������.
        