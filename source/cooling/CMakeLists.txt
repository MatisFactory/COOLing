cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

include(../../cmake/AutoSourceGroup.cmake)

set(FILES
     test_dll.cpp
     test_dll.hpp
     export/cooling_dll.hpp)

add_library(cooling SHARED
	${FILES})

AUTO_GROUP_SOURCE(${FILES})
