include(cmake/EnableVcpkg.cmake)
cmake_minimum_required(VERSION 3.22)
project(qt-gui-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED
)

include_directories(include source)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "source/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

function(link_common_libraries target)
    target_link_libraries(${target}
        PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
    )
endfunction(link_common_libraries)

link_common_libraries(${PROJECT_NAME})