Project ( Kas )

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
  FIND_PACKAGE(Git)
  IF(GIT_FOUND)
    EXECUTE_PROCESS(
      COMMAND ${GIT_EXECUTABLE} describe --always --dirty
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "GITVERSION"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    MESSAGE( STATUS "Git version: ${GITVERSION}" )
  ELSE(GIT_FOUND)
    SET(GITVERSION 0)
  ENDIF(GIT_FOUND)
ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/jni/src/gitversion.h.in ${CMAKE_CURRENT_SOURCE_DIR}/jni/src/gitversion.h @ONLY)

Find_Package ( SDL2 REQUIRED )

if ( NOT SDL2_FOUND )
   message ( FATAL_ERROR "SDL2 not found!" )
endif ( NOT SDL2_FOUND )

Find_Package (SDL2GFX REQUIRED )

if ( NOT SDL2GFX_FOUND )
   message ( FATAL_ERROR "SDL2_gfx not found!" )
endif ( NOT SDL2GFX_FOUND )

Find_Package (SDL2TTF REQUIRED )

if ( NOT SDL2TTF_FOUND )
   message ( FATAL_ERROR "SDL2_ttf not found!" )
endif ( NOT SDL2TTF_FOUND )

set(BOX2D_VERSION 2.1.0)
set(BOX2D_BUILD_STATIC ON)
add_subdirectory(${CMAKE_SOURCE_DIR}/jni/Box2D/)
include_directories(${CMAKE_SOURCE_DIR}/jni/)
add_subdirectory(jni/src/)

add_subdirectory(assets/)