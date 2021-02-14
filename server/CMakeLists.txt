cmake_minimum_required(VERSION 3.14)

project(server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5Network)

list(APPEND SOURCES
    src/file_info.cpp
    src/filesystem.cpp
    src/http_server.cpp
    src/main.cpp)

list(APPEND QOBJECTS
    include/http_server.h
    include/file_info.h
    include/file_type.h
    include/filesystem.h)

set(HTTP_PARSER_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../common/libHttpParser.a)
set(HTTP_PARSER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)

add_executable(${PROJECT_NAME} ${SOURCES} ${QOBJECTS})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network)

target_link_libraries(${PROJECT_NAME} ${HTTP_PARSER_LIB})

target_include_directories(${PROJECT_NAME} PUBLIC ${HTTP_PARSER_INCLUDE_DIR})


