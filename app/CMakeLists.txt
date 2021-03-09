cmake_minimum_required(VERSION 3.7)

project(meteor_radio_app VERSION 1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
find_package(GSL REQUIRED)    # See below (2)
find_package(PostgreSQL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${Qt5Network_INCLUDE_DIRS}
                    ${GSL_INCLUDE_DIRS}
                    ${gis_patrol_INCLUDE_DIRS}
                    )

set(HEADERS
    meteorRadioMainWindow.h
)

set(FORMS
    meteor_radio_main_window.ui
)

set(SOURCES
    meteorRadioMainWindow.cpp
    main.cpp
)

set(RESOURCES
    ../gis_patrol_rubin/gis_patrol_client/src/patrol_icons/patrol.qrc
    ../gis_patrol_rubin/gis_patrol_client/gis_patrol.qrc
)

qt5_wrap_ui(UIS_HDRS ${FORMS} )

include_directories(../src ../src/maths ../src/radioStations ../src/meteorTraces)
include_directories(../gis_patrol_rubin/gis_patrol_client/src ../gis_patrol_rubin/gis_patrol_client/src/corelibs ../../src/factories/guifactory ../gis_patrol_rubin/gis_patrol_client/src/patrolCommunications ../gis_patrol_rubin/gis_patrol_client/src/factories/pgui )

link_directories(${CMAKE_SOURCE_DIR}/build/src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src/maths)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../gis_patrol_rubin/gis_patrol_client)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../gis_patrol_rubin/gis_patrol_client/src/)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS_HDRS} ${RESOURCES}  )

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Network meteor_radio meteor_radio_maths GSL::gsl GSL::gslcblas ${PostgreSQL_LIBRARIES} dataaccess corelibs pgui guifactory )

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
)
