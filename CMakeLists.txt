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

# Add library
add_library(attendee STATIC 
	"source/attendee/ssl.cpp"
	"source/attendee/response.cpp"
	"source/attendee/request.cpp"
	"source/attendee/core.cpp"
	"source/attendee/cookie.cpp"
	"source/attendee/cookie_proxy.cpp"
	"source/attendee/cookie_iterator.cpp"
	"source/attendee/sources/file_source.cpp"
	"source/attendee/sources/stream_source.cpp"
	"source/attendee/sources/string_source.cpp"
)

find_package(CURL REQUIRED)

target_link_libraries(attendee PUBLIC CURL::libcurl)

# MS SOCK
if (WIN32)	
	target_link_libraries(attendee PRIVATE -lws2_32 -lmswsock)
	
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		target_compile_definitions(attendee PRIVATE BOOST_USE_WINDOWS_H=1)
	endif()
else()
endif()

target_include_directories(attendee PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Compiler Options
set(DEBUG_OPTIONS -fexceptions -g -Wall -pedantic-errors -pedantic -Wfloat-equal -fstrict-aliasing -Wstrict-aliasing)
set(RELEASE_OPTIONS -fexceptions -O3 -Wall -pedantic-errors -pedantic -fstrict-aliasing -Wstrict-aliasing)
target_compile_options(attendee PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(attendee PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")