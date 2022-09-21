cmake_minimum_required(VERSION 3.14...3.22)
include(cmake/prefix.cmake)
project(devcore CXX)
include(cmake/postfix.cmake)

add_library(walker INTERFACE)
target_include_directories(walker INTERFACE ${PROJECT_SOURCE_DIR})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(catch2)
  include(standards)
  FetchContent_MakeAvailable(${FetchContents})
endif()

add_subdirectory(benchmark)
add_subdirectory(example)
