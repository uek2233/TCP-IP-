set(SOURCE 
  fork.c
)
set(OBJECTS "")

get_filename_component(CURRENT_DIR_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CURRENT_DIR_NAME})

foreach(src IN LISTS SOURCE)
    get_filename_component(obj ${src} NAME_WE)
    list(APPEND OBJECTS "${obj}.o")
    add_executable(${obj} ${src})
    if(CMAKE_INCLUDE_PATH)
        target_include_directories(${obj} PRIVATE ${CMAKE_INCLUDE_PATH})
    endif()
    message(STATUS "可执行文件输出路径: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${obj}")
endforeach()

message(STATUS "当前目录名字是: ${CURRENT_DIR_NAME}")
message(STATUS "源文件: ${SOURCE}")
message(STATUS "目标文件: ${OBJECTS}")