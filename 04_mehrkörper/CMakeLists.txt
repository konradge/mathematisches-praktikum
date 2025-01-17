# Copyright (c) 2022, The MaPra Authors.

cmake_minimum_required(VERSION 3.13.3 FATAL_ERROR)
cmake_policy(VERSION 3.13.3)
# ##############################################################################
# Build type (needs to be handled before project command below)
# ##############################################################################
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE
        STRING
        "Configuration type (one of Debug, Release, RelWithDebInfo, MinSizeRel)"
  )
endif()
set(CMAKE_CXX_FLAGS "-O3")
message(STATUS "The build type is ${CMAKE_BUILD_TYPE}")
#
# ##############################################################################
# Project metadata
# ##############################################################################
project(
  mapra
  LANGUAGES CXX
  VERSION 1.0.0)

# ##############################################################################
# Find dependencies
# ##############################################################################

include(${mapra_SOURCE_DIR}/cmake/dependencies.cmake)

# ##############################################################################
# Add some helper functions to make this more pretty for you
# ##############################################################################
include(${mapra_SOURCE_DIR}/cmake/functions.cmake)

# ##############################################################################
# Unit Testing
# ##############################################################################

enable_testing()
mapra_add_test(matrix_test)
mapra_add_test(vector_test)
# Add new tests via mapra_add_test(filename)

# ##############################################################################
# This function will create the makefiles for your solution
# ##############################################################################

mapra_add_executable(loesung src/loesung.cpp)
