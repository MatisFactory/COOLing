function(AUTO_GROUP_SOURCE)

foreach(FILE IN LISTS ARGN)
  get_filename_component(PARENT_DIR "${FILE}" PATH)

  string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")

  if ("${FILE}" MATCHES ".*\\.cpp")
    set(GROUP "${GROUP}")
  elseif("${FILE}" MATCHES ".*\\.hpp")
    set(GROUP "${GROUP}")
  endif()

  source_group("${GROUP}" FILES "${FILE}")
endforeach()

endfunction()