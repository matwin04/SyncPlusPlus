cmake_minimum_required(VERSION 3.15)
project(SyncPlusPlus)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
# Try to find Qt6 first
find_package(Qt6 COMPONENTS Core Sql Widgets Network QUIET)
# If Qt6 is not found, fallback to Qt5
if (NOT Qt6_FOUND)
    message(STATUS "Qt6 not found, falling back to Qt5.")
    find_package(Qt5 COMPONENTS Core Sql Widgets Network REQUIRED)
    set(QT_LIBRARIES
        Qt5::Core
        Qt5::Sql
        Qt5::Widgets
        Qt5::Network
    )
else()
    message(STATUS "Using Qt6.")
    set(QT_LIBRARIES
        Qt6::Core
        Qt6::Sql
        Qt6::Widgets
        Qt6::Network
    )
endif()

# Include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
set(SOURCES
        main.cpp
        sync.cpp
        mainwindow.cpp
        )

# Add header files
set(HEADERS
        sync.h
        mainwindow.h
)

# Add UI files
set(UI_FILES
        ui/mainwindow.ui

        )

# Add executable
add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
        )


# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
install(FILES config.ini DESTINATION ${CMAKE_BINARY_DIR})

