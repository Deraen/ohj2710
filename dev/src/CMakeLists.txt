include_directories(${SDL2_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE})

set(SOURCES
	main.cc)

add_executable(
	Kas
	WIN32
	MACOSX_BUNDLE
	${SOURCES}
	)

target_link_libraries (
	Kas
 	${SDL2_LIBRARY}
 	Box2D
)
