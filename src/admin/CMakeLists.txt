FIND_PACKAGE(Qt4 REQUIRED)

# TODO:
#    1) Проверка наличия Qt. 
#    2) Проверка совпадения версий компиляторов Qt и данного.
#    3) Разобраться с QT_USE_FILE.
#    4) Копировать библиотеки (dll) Qt в output dir (под windows).

SET(admin_SOURCES main.cpp admin.cpp)
SET(admin_HEADERS admin.h)
SET(admin_FORMS admin.ui)
SET(admin_RESOURCES admin.qrc)

QT4_WRAP_CPP(admin_HEADERS_MOC ${admin_HEADERS})
QT4_WRAP_UI(admin_FORMS_HEADERS ${admin_FORMS})
QT4_ADD_RESOURCES(admin_RESOURCES_RCC ${admin_RESOURCES})

INCLUDE(${QT_USE_FILE}) # TODO: разобраться

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_EXECUTABLE(admin 
    ${admin_SOURCES} 
    ${admin_HEADERS_MOC} 
    ${admin_FORMS_HEADERS} 
    ${admin_RESOURCES_RCC})

TARGET_LINK_LIBRARIES(admin ${QT_LIBRARIES})