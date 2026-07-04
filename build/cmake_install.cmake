# Install script for directory: /root/TCP-IP

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/TCP-IP/build/7.1/cmake_install.cmake")
  include("/root/TCP-IP/build/8.1/cmake_install.cmake")
  include("/root/TCP-IP/build/9.1/cmake_install.cmake")
  include("/root/TCP-IP/build/9.2/cmake_install.cmake")
  include("/root/TCP-IP/build/10.1/cmake_install.cmake")
  include("/root/TCP-IP/build/10.2/cmake_install.cmake")
  include("/root/TCP-IP/build/10.3/cmake_install.cmake")
  include("/root/TCP-IP/build/10.4/cmake_install.cmake")
  include("/root/TCP-IP/build/10.5/cmake_install.cmake")
  include("/root/TCP-IP/build/11.1/cmake_install.cmake")
  include("/root/TCP-IP/build/11.2/cmake_install.cmake")
  include("/root/TCP-IP/build/12.1/cmake_install.cmake")
  include("/root/TCP-IP/build/13.1/cmake_install.cmake")
  include("/root/TCP-IP/build/13.2/cmake_install.cmake")
  include("/root/TCP-IP/build/14.1/cmake_install.cmake")
  include("/root/TCP-IP/build/14.2/cmake_install.cmake")
  include("/root/TCP-IP/build/15.1/cmake_install.cmake")
  include("/root/TCP-IP/build/15.2/cmake_install.cmake")
  include("/root/TCP-IP/build/16.1/cmake_install.cmake")
  include("/root/TCP-IP/build/17.1/cmake_install.cmake")
  include("/root/TCP-IP/build/17.2/cmake_install.cmake")
  include("/root/TCP-IP/build/18.1/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/root/TCP-IP/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
