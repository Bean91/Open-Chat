cmake_minimum_required(VERSION 3.14)
project(openchat)

add_subdirectory(vendor/llama.cpp)

add_executable(openchat chat.cpp)
target_link_libraries(openchat llama)