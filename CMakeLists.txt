cmake_minimum_required(VERSION 3.20)
project(openchat)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif()

add_executable(openchat chat.cpp)
add_executable(tokentrainer training/tokenizer_trainer.cpp)
add_executable(modeltrainer training/model_trainer.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)
