# Version check
cmake_minimum_required (VERSION 3.0)

if(NOT "${CMAKE_CXX_STANDARD}")
	set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

# Project
project(attendee)

# Add files
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/source/attendee/*.cpp")

# Add library
add_library(attendee STATIC ${sources})

find_library(LCURL curl)

set(LIBS "${LCURL}")

# MS SOCK
if (WIN32)	
	set(LIBS "${LIBS} -lws2_32 -lmswsock")
	
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		target_compile_definitions(attendee PRIVATE BOOST_USE_WINDOWS_H=1)
	endif()
else()
endif()

target_include_directories(attendee PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(attendee PRIVATE "${LIBS}")

# Compiler Options
set(DEBUG_OPTIONS -fexceptions -g -Wall -pedantic-errors -pedantic -Wfloat-equal -fstrict-aliasing -Wstrict-aliasing)
set(RELEASE_OPTIONS -fexceptions -O3 -Wall -pedantic-errors -pedantic -fstrict-aliasing -Wstrict-aliasing)
target_compile_options(attendee PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(attendee PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")