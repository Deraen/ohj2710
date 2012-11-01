include_directories(${SDL2_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE})
include_directories(.)

add_custom_target(build-assets
	COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/build-assets.py"
	COMMENT "Generating Assets.cpp/hpp"
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

set(SOURCES
	main.cpp
	Game.cpp
	Screen.cpp
	Assets.cpp
	Object.cpp
	objects/Asteroid.cpp
	objects/Bomb.cpp
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
	Box2D
)

add_dependencies(peli build-assets)
