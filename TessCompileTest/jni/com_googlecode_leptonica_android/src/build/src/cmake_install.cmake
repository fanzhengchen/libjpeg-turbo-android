# Install script for directory: /home/mark/leptonica-1.74.4/src

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/mark/leptonica-1.74.4/build/src/libleptonica.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libleptonica.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libleptonica.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/mark/Android/Sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libleptonica.so")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/LeptonicaTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/LeptonicaTargets.cmake"
         "/home/mark/leptonica-1.74.4/build/src/CMakeFiles/Export/cmake/LeptonicaTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/LeptonicaTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/LeptonicaTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "/home/mark/leptonica-1.74.4/build/src/CMakeFiles/Export/cmake/LeptonicaTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "/home/mark/leptonica-1.74.4/build/src/CMakeFiles/Export/cmake/LeptonicaTargets-noconfig.cmake")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/leptonica" TYPE FILE FILES
    "/home/mark/leptonica-1.74.4/src/allheaders.h"
    "/home/mark/leptonica-1.74.4/src/alltypes.h"
    "/home/mark/leptonica-1.74.4/src/array.h"
    "/home/mark/leptonica-1.74.4/src/arrayaccess.h"
    "/home/mark/leptonica-1.74.4/src/bbuffer.h"
    "/home/mark/leptonica-1.74.4/src/bilateral.h"
    "/home/mark/leptonica-1.74.4/src/bmf.h"
    "/home/mark/leptonica-1.74.4/src/bmfdata.h"
    "/home/mark/leptonica-1.74.4/src/bmp.h"
    "/home/mark/leptonica-1.74.4/src/ccbord.h"
    "/home/mark/leptonica-1.74.4/src/dewarp.h"
    "/home/mark/leptonica-1.74.4/src/environ.h"
    "/home/mark/leptonica-1.74.4/src/gplot.h"
    "/home/mark/leptonica-1.74.4/src/heap.h"
    "/home/mark/leptonica-1.74.4/src/imageio.h"
    "/home/mark/leptonica-1.74.4/src/jbclass.h"
    "/home/mark/leptonica-1.74.4/src/leptwin.h"
    "/home/mark/leptonica-1.74.4/src/list.h"
    "/home/mark/leptonica-1.74.4/src/morph.h"
    "/home/mark/leptonica-1.74.4/src/pix.h"
    "/home/mark/leptonica-1.74.4/src/ptra.h"
    "/home/mark/leptonica-1.74.4/src/queue.h"
    "/home/mark/leptonica-1.74.4/src/rbtree.h"
    "/home/mark/leptonica-1.74.4/src/readbarcode.h"
    "/home/mark/leptonica-1.74.4/src/recog.h"
    "/home/mark/leptonica-1.74.4/src/regutils.h"
    "/home/mark/leptonica-1.74.4/src/stack.h"
    "/home/mark/leptonica-1.74.4/src/stringcode.h"
    "/home/mark/leptonica-1.74.4/src/sudoku.h"
    "/home/mark/leptonica-1.74.4/src/watershed.h"
    "/home/mark/leptonica-1.74.4/build/src/endianness.h"
    )
endif()

