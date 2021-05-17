cmake_minimum_required(VERSION 3.1)

project(SHA256 CXX)

if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MINGW")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  MESSAGE("-- GNU Toolchain detected")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  MESSAGE("-- MSVC Toolchain detected")
  set ( CXX_STANDARD 14 )
else()
  set ( CXX_STANDARD 14 ) 
endif()

add_executable( SHA256_TEST test/main.cpp sha256.cpp )

enable_testing()

add_test( SHA256_EXECUTION SHA256_TEST )
