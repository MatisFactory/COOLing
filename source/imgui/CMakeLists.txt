cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(imgui)

include(../../cmake/AutoSourceGroup.cmake)

set(FILES
	imconfig.h
	imgui.cpp
	imgui.h
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_impl_glfw_gl3.cpp
	imgui_impl_glfw_gl3.h
	imgui_internal.h
	stb_rect_pack.h
	stb_textedit.h
	stb_truetype.h)

add_library(
	imgui STATIC
	${FILES})

target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS imgui
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)

AUTO_GROUP_SOURCE(${FILES})