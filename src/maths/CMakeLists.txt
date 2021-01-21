cmake_minimum_required(VERSION 3.7)

project(meteor_radio_maths VERSION 1.0)

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
find_package(GSL REQUIRED)
find_package(PostgreSQL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${GSL_INCLUDE_DIRS}
                    ${gis_patrol_INCLUDE_DIRS}
                    )

include_directories( ./gui ./gui/ui ../../gis_patrol_rubin/gis_patrol_client/src ../../gis_patrol_rubin/gis_patrol_client/src/corelibs)

set(HEADERS
    randomNumbGenerator.h
    uniRandomNumbGenerator.h
    expRandomNumbGenerator.h
    gaussianRandomNumbGenerator.h
    rayleighRandomNumbGenerator.h
)

set(FORMS
)

set(SOURCES
    randomNumbGenerator.cpp
    uniRandomNumbGenerator.cpp
    expRandomNumbGenerator.cpp
    gaussianRandomNumbGenerator.cpp
    rayleighRandomNumbGenerator.cpp
)

set(RESOURCES
)

#qt5_wrap_ui(UIS_HDRS ${FORMS} )

link_directories(${CMAKE_SOURCE_DIR}/build/src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../../gis_patrol_rubin/gis_patrol_client/src/)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../../gis_patrol_rubin/gis_patrol_client/src/corelibs)
link_directories(${CMAKE_SOURCE_DIR}/build/gis_patrol_rubin/gis_patrol_client/src/corelibs)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${RESOURCES} ${PostgreSQL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets GSL::gsl GSL::gslcblas ${PostgreSQL_LIBRARIES} )

set(${PROJECT_NAME}_RUNTIME_LIBRARY_DIRS ${CMAKE_INSTALL_LIBDIR} )

target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include/${PROJECT_NAME}> ${PostgreSQL_INCLUDE_DIRS})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION lib
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
