cmake_minimum_required (VERSION 3.1.0)

project(test_Qt)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

file(GLOB_RECURSE SRC *.ui *.cpp)
file(GLOB_RECURSE HDR *.h)
find_package(Qt5 COMPONENTS Gui Core Widgets PrintSupport REQUIRED)

add_executable(${PROJECT_NAME} WIN32 ${SRC} ${HDR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::PrintSupport)
