cmake_minimum_required(VERSION 3.14)

project(client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Core Network Gui Qml Quick QuickControls2 REQUIRED)

list(APPEND SOURCES
    src/client.cpp
    src/client.h
    src/main.cpp
    src/fileinfo.h
    src/fileinfo.cpp)


set(HTTP_PARSER_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../common/libHttpParser.a)
set(HTTP_PARSER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)



add_executable(${PROJECT_NAME} ${SOURCES} client.qrc)

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} ${HTTP_PARSER_LIB})

target_include_directories(${PROJECT_NAME} PUBLIC ${HTTP_PARSER_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Network
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2)

