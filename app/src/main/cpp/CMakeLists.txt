
cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/include ${PWD})
add_library(
             imageproc
             SHARED
             imageproc.cpp)

set(LIB_DIR ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})

add_library(jpeg SHARED IMPORTED)
set_target_properties(jpeg PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/libjpeg.so)

add_library(turbojpeg SHARED IMPORTED)
set_target_properties(turbojpeg PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/libturbojpeg.so)


target_link_libraries( imageproc
                       log
                       jpeg
                       jnigraphics
                       turbojpeg
                       )