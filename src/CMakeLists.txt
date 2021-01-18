cmake_minimum_required(VERSION 3.7)

project(meteor_radio VERSION 1.0)

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

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${gis_patrol_INCLUDE_DIRS}
                    )

include_directories( ./gui ./gui/ui ../gis_patrol_rubin/gis_patrol_client/src
    ../gis_patrol_rubin/gis_patrol_client/src/corelibs
    ../gis_patrol_rubin/gis_patrol_client/src/dataaccess
    ../gis_patrol_rubin/gis_patrol_client/src/patrolCommunications
    ./meteorRadioEntities ./maths )

set(HEADERS
    meteorRadioSingleton.h
    meteorRadioStationsFactory.h
    meteorLoader.h
    meteorWriter.h
    meteor_constants.h
    gui/ui/meteorRadioNetworkForm.h
    gui/ui/meteorRadioStationForm.h
)

set(FORMS
    gui/ui/meteor_radio_network_form.ui
    gui/ui/meteor_radio_station_form.ui
)

set(SOURCES
    meteorRadioSingleton.cpp
    meteorRadioStationsFactory.cpp
    meteorLoader.cpp
    meteorWriter.cpp
    gui/ui/meteorRadioNetworkForm.cpp
    gui/ui/meteorRadioStationForm.cpp
)

set(RESOURCES
)

qt5_wrap_ui(UIS_HDRS ${FORMS} )

find_package(GSL REQUIRED)    # See below (2)
find_package(PostgreSQL REQUIRED)

link_directories(${CMAKE_SOURCE_DIR}/build/src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src/maths)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src/meteorRadioEntities)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../gis_patrol_rubin/gis_patrol_client/src/)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../gis_patrol_rubin/gis_patrol_client/src/corelibs)
link_directories(${CMAKE_SOURCE_DIR}/build/gis_patrol_rubin/gis_patrol_client/src/corelibs)
message(STATUS "patrols link dir is ${CMAKE_SOURCE_DIR}/build/gis_patrol_rubin/gis_patrol_client/src/corelibs")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${UIS_HDRS} ${RESOURCES} ${PostgreSQL_LIBRARIES} ${meteor_radio_maths_LIBRARIES} ${meteor_radio_entities_LIBRARIES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets GSL::gsl GSL::gslcblas ${PostgreSQL_LIBRARIES} dataaccess corelibs pgui guifactory ${meteor_radio_maths_LIBRARIES} meteor_radio_entities)

set(${PROJECT_NAME}_RUNTIME_LIBRARY_DIRS ${CMAKE_INSTALL_LIBDIR} )

target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include/${PROJECT_NAME}> ${PostgreSQL_INCLUDE_DIRS})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION lib
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
add_subdirectory(maths)
add_subdirectory(meteorRadioEntities)
