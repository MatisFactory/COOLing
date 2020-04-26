cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(main)

include(../../cmake/AutoSourceGroup.cmake)

set(FILES
     main.cpp
	 core/application.cpp
	 core/application.hpp
	 core/window.cpp
	 core/window.hpp
	 core/settings/window_settings.hpp
	 core/shader/shader.hpp
	 models/cube.cpp
	 models/cube.hpp
	 )

add_executable(main ${FILES})

target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

AUTO_GROUP_SOURCE(${FILES})

install(TARGETS main
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)

target_link_libraries(main PRIVATE cooling)
set_target_properties(cooling PROPERTIES LINKER_LANGUAGE CXX)