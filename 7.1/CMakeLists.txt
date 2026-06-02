get_filename_component(CURRENT_DIR_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CURRENT_DIR_NAME})

add_executable(file_client file_client.c)
add_executable(file_server file_server.c)

if(CMAKE_INCLUDE_PATH)
  target_include_directories(file_client PRIVATE ${CMAKE_INCLUDE_PATH})
  target_include_directories(file_server PRIVATE ${CMAKE_INCLUDE_PATH})
endif()

