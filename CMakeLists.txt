# Version check
cmake_minimum_required (VERSION 3.0)

# Project
project(attendee)

function(add_cxx_compiler_flag FLAG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG}" PARENT_SCOPE)
endfunction()

if (NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler Options
add_cxx_compiler_flag("-std=c++14")
add_cxx_compiler_flag("-Wall")
add_cxx_compiler_flag("-Wall")
add_cxx_compiler_flag("-Wextra")
add_cxx_compiler_flag("-pedantic")
add_cxx_compiler_flag("-pedantic-errors")
add_cxx_compiler_flag("-Wfloat-equal")
add_cxx_compiler_flag("-fstrict-aliasing")
add_cxx_compiler_flag("-Wstrict-aliasing")
add_cxx_compiler_flag("-O3")

# Add files
file(GLOB_RECURSE sources "attendee/*.cpp" "attendee/source/*.cpp")

# Add library
add_library(attendee STATIC ${sources})

find_library(LCURL curl)

set(LIBS "${LCURL}")

# MS SOCK
if (WIN32)
	find_library(LWS2_32 ws2_32)
	find_library(LMSWSOCK mswsock)
	
	set(LIBS "${LIBS} ${LWS2_32} ${LMSWSOCK}")
	
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		target_compile_definitions(attendee PRIVATE BOOST_USE_WINDOWS_H=1)
	endif()
else()
endif()

target_link_libraries(attendee PRIVATE "${LIBS}")