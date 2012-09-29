Project ( Kas )

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

Find_Package ( SDL2 REQUIRED )

if ( NOT SDL2_FOUND )
   message ( FATAL_ERROR "SDL2 not found!" )
endif ( NOT SDL2_FOUND )

find_package( OpenGLES REQUIRED )

if ( NOT OPENGLES_FOUND )
	message ( FATAL_ERROR "OpenGLES not found!" )
endif ( NOT OPENGLES_FOUND )

set(BOX2D_VERSION 2.1.0)
set(BOX2D_BUILD_STATIC ON)
add_subdirectory(${CMAKE_SOURCE_DIR}/jni/Box2D/)
#include_directories(${CMAKE_SOURCE_DIR}/lib/)

add_subdirectory(jni/src/)
