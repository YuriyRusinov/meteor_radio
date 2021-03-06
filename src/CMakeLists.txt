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
#find_package(Qwt REQUIRED)

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
    ./meteorRadioEntities ./maths ./radioStations ./meteorTraces )

set(HEADERS
    meteorRadioSingleton.h
    meteorLoader.h
    meteorWriter.h
    radioStations/meteorRadioStationsFactory.h
    radioStations/meteorRadioController.h
    radioStations/meteorRadioWorker.h
    meteorTraces/meteorTraceGenerationFactory.h
    meteorTraces/meteorTraceController.h
    meteorTraces/meteorTraceWorker.h
    meteor_constants.h
)

set(SOURCES
    meteorRadioSingleton.cpp
    meteorLoader.cpp
    meteorWriter.cpp
    radioStations/meteorRadioStationsFactory.cpp
    radioStations/meteorRadioController.cpp
    radioStations/meteorRadioWorker.cpp
    meteorTraces/meteorTraceGenerationFactory.cpp
    meteorTraces/meteorTraceController.cpp
    meteorTraces/meteorTraceWorker.cpp
)

set(RESOURCES
)

qt5_wrap_ui(UIS_HDRS ${FORMS} )

find_package(GSL REQUIRED)    # See below (2)
find_package(PostgreSQL REQUIRED)

add_subdirectory( ./gui )
add_subdirectory(maths)
add_subdirectory(meteorRadioEntities)

link_directories(${CMAKE_SOURCE_DIR}/build/src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src/maths)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src/meteorRadioEntities)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../gis_patrol_rubin/gis_patrol_client/src/)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../gis_patrol_rubin/gis_patrol_client/src/corelibs)
link_directories(${CMAKE_SOURCE_DIR}/build/gis_patrol_rubin/gis_patrol_client/src/corelibs)
message(STATUS "patrols link dir is ${CMAKE_SOURCE_DIR}/build/gis_patrol_rubin/gis_patrol_client/src/corelibs")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${UIS_HDRS} ${RESOURCES} ${PostgreSQL_LIBRARIES} ${meteor_radio_maths_LIBRARIES} ${meteor_radio_entities_LIBRARIES} ${meteor_radio_gui_LIBRARIES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets GSL::gsl GSL::gslcblas ${PostgreSQL_LIBRARIES} dataaccess corelibs pgui guifactory ${meteor_radio_maths_LIBRARIES} meteor_radio_entities meteor_radio_gui meteor_radio_maths)

set(${PROJECT_NAME}_RUNTIME_LIBRARY_DIRS ${CMAKE_INSTALL_LIBDIR} )

target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include/${PROJECT_NAME}> ${PostgreSQL_INCLUDE_DIRS})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION lib
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
