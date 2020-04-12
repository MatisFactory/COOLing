cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(COOLing)

include(cmake/AutoSourceGroup.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(COOLing)

set(FILES
     main.cpp)

add_executable(main ${FILES})

AUTO_GROUP_SOURCE(${FILES})

install(TARGETS main
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)

target_link_libraries(main PRIVATE cooling)
set_target_properties(cooling PROPERTIES LINKER_LANGUAGE CXX)