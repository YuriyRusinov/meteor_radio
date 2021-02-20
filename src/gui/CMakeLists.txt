cmake_minimum_required(VERSION 3.7)

project(meteor_radio_gui VERSION 1.0)

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

include_directories( ../ ./ui ../../gis_patrol_rubin/gis_patrol_client/src
    ../../gis_patrol_rubin/gis_patrol_client/src/factories/pgui
)

set(HEADERS
    meteorRadioStationsModel.h
    randomParametersModel.h
    meteorDelegate.h
    ui/meteorRadioNetworkForm.h
    ui/meteorRadioStationForm.h
)

set(FORMS
    ui/meteor_radio_network_form.ui
    ui/meteor_radio_station_form.ui
)

set(SOURCES
    meteorRadioStationsModel.cpp
    randomParametersModel.cpp
    meteorDelegate.cpp
    ui/meteorRadioNetworkForm.cpp
    ui/meteorRadioStationForm.cpp
)

set(RESOURCES
)

qt5_wrap_ui(UIS_HDRS ${FORMS} )

link_directories(${CMAKE_SOURCE_DIR}/build/src)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${UIS_HDRS} ${RESOURCES} )

target_link_libraries(${PROJECT_NAME} Qt5::Widgets pgui guifactory )

set(${PROJECT_NAME}_RUNTIME_LIBRARY_DIRS ${CMAKE_INSTALL_LIBDIR} )

target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include/${PROJECT_NAME}> ${PostgreSQL_INCLUDE_DIRS})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION lib
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
