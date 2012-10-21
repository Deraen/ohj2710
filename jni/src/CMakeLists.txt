include_directories(${SDL2_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE})
include_directories(.)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

set(SOURCES
	main.cpp
	Object.cpp
	World.cpp
	Manager.cpp
	Screen.cpp
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
