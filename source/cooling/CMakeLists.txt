cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(cooling)

include(../../cmake/AutoSourceGroup.cmake)

set(FILES
     frustum_view.cpp
     frustum_view.hpp
     export/cooling_dll.hpp)

add_library(cooling SHARED
	${FILES})

AUTO_GROUP_SOURCE(${FILES})

target_include_directories(cooling PUBLIC "${CMAKE_SOURCE_DIR}/source")
