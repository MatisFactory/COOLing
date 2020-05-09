cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(main)

include(../../cmake/AutoSourceGroup.cmake)

set(FILES
     main.cpp
	 core/application.cpp
	 core/application.hpp
	 core/culling_wrapper.hpp
	 core/window.cpp
	 core/window.hpp
	 core/camera/camera.cpp
	 core/camera/camera.hpp
	 core/camera/camera_manager.cpp
	 core/camera/camera_manager.hpp
	 core/clock/clock.cpp
	 core/clock/clock.hpp
	 core/drawers/camera_drawer.cpp
	 core/drawers/camera_drawer.hpp
	 core/drawers/obj_model_drawer.cpp
	 core/drawers/obj_model_drawer.hpp
	 core/settings/scene_settings.hpp
	 core/settings/window_settings.hpp
	 core/shader/shader.hpp
	 core/signal/signal.hpp
	 models/cube_manager.cpp
	 models/cube_manager.hpp
	 models/cube.cpp
	 models/cube.hpp
	 third_party/OBJ_Loader.h
	 )

add_executable(main ${FILES})

# target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/source")


AUTO_GROUP_SOURCE(${FILES})

install(TARGETS main
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)

target_link_libraries(main PRIVATE 
	cooling
	imgui)

set_target_properties(cooling PROPERTIES LINKER_LANGUAGE CXX)