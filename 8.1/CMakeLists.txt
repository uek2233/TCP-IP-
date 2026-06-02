set(SOURCE 
  getthostbyname.c
  gethostbyaddr.c
)
set(OBJECTS "")

get_filename_component(CURRENT_DIR_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CURRENT_DIR_NAME})

foreach(src IN LISTS SOURCE)
  get_filename_component(obj ${src} NAME_WE)
  list(APPEND OBJECTS "${obj}.o")
  # 1. 先创建可执行文件（必须放第一！）
  add_executable(${obj} ${src})
  # 2. 再设置头文件路径（顺序不能反！）
  if(CMAKE_INCLUDE_PATH)
    target_include_directories(${obj} PRIVATE ${CMAKE_INCLUDE_PATH})
  endif()
endforeach()


message(STATUS "当前目录名字是: ${CURRENT_DIR_NAME}")
message(STATUS "源文件: ${SOURCE}")
message(STATUS "目标文件: ${OBJECTS}")






