
cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp )

set(LIB_DIR ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})

add_library(jpeg SHARED IMPORTED)
set_target_properties(jpeg PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/libjpeg.so)

add_library(turbojpeg SHARED IMPORTED)
set_target_properties(turbojpeg PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/libturbojpeg.so)

find_library( # Sets the name of the path variable.
              log-lib
              jpeg
              turbojpeg
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )



target_link_libraries( native-lib
                       log-lib
                       )