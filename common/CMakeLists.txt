cmake_minimum_required(VERSION 3.14)

project(HttpParser LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

list(APPEND SOURCES
        src/http_message.cpp
        src/http_request.cpp
        src/http_request_parser.cpp
        src/http_response.cpp
        src/http_response_parser.cpp)

list(APPEND HEADERS
        include/http_message.h
        include/http_request.h
        include/http_request_parser.h
        include/http_response.h
        include/http_response_parser.h)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} Qt5::Core)