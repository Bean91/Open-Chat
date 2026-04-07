cmake_minimum_required(VERSION 3.20)
project(openchat)

add_executable(openchat chat.cpp)

set_target_properties(openchat PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(openchat PRIVATE ${CMAKE_SOURCE_DIR}/include)