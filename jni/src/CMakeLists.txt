include_directories(${SDL2_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE})
include_directories(${SDL2TTF_INCLUDE_DIR})
include_directories(.)

add_custom_target(build-assets
	COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/build-assets.py"
	COMMENT "Generating Assets.cpp/hpp"
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	)

SET_SOURCE_FILES_PROPERTIES("${CMAKE_CURRENT_SOURCE_DIR}/Assets.cpp" PROPERTIES GENERATED TRUE)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath=$ORIGIN/")

set(SOURCES
	main.cpp
	Game.cpp
	Screen.cpp
	Assets.cpp
	Object.cpp
	DebugDraw.cpp
	UI.cpp
	interfaces/Drawable.cpp
	objects/Asteroid.cpp
	objects/Bomb.cpp
	objects/Laser.cpp
	objects/Planet.cpp
	objects/Sprite.cpp
	)

add_executable(
	peli
	WIN32
	MACOSX_BUNDLE
	${SOURCES}
	)

target_link_libraries (
	peli
	${SDL2_LIBRARY}
	${SDL2GFX_LIBRARY}
	${SDL2TTF_LIBRARY}
	Box2D
)

add_dependencies(peli build-assets)

add_custom_command(TARGET peli
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/peli ${CMAKE_CURRENT_BINARY_DIR}/../..)
