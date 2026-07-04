cmake_minimum_required(VERSION 3.10)
project(tcp_ip_examples LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Allow the shell build script to export CC and C_INCLUDE_PATH from .tools.
if(NOT DEFINED CMAKE_C_COMPILER AND DEFINED ENV{CC})
  set(CMAKE_C_COMPILER $ENV{CC} CACHE FILEPATH "C compiler")
endif()

if(DEFINED ENV{C_INCLUDE_PATH})
  list(APPEND CMAKE_INCLUDE_PATH $ENV{C_INCLUDE_PATH})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SUBDIRS
    7.1
    8.1
    9.1
    9.2
    10.1
    10.2
    10.3
    10.4
    10.5
    11.1
    11.2
    12.1
    13.1
    13.2
    14.1
    14.2
    15.1
    15.2
    16.1
    17.1
    17.2
    18.1
    )
foreach(subdir IN LISTS SUBDIRS)
  add_subdirectory(${subdir})
endforeach()

