include_directories(${SDL2_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE})

SET(CMAKE_CXX_FLAGS "-std=c++0x")

set(SOURCES
	main.cpp
	Object.cpp
	managers/DrawableManager.cpp
	objects/Asteroid.cpp
	objects/Bomb.cpp
	objects/Hitbox.cpp
	objects/Planet.cpp
	objects/Player.cpp
	objects/Drawable.cpp
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
	${OpenGLES_LIBRARIES}
	Box2D
)
