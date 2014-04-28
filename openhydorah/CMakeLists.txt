option (BUILD_TESTS "Build tests" ON)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

include_directories(include)
file (GLOB SRC src/*.c src/init/*.c src/editor/*.c)

add_executable(hydorah ${SRC})
target_link_libraries(hydorah jansson)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/assets)
		if (WIN32)
			file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
		else ()
				ADD_CUSTOM_COMMAND (
					TARGET hydorah POST_BUILD
					COMMAND ln -s ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
					COMMENT "Creating symbolic link"
				)
		endif ()
	endif ()
endif ()

if (NOT WIN32)
	target_link_libraries(hydorah -lm)
endif ()

find_package(SDL2 REQUIRED)
if (${SDL_FOUND})
	include_directories(${SDL_INCLUDE_DIR})
	target_link_libraries(hydorah ${SDL_LIBRARY})
endif ()

find_package(SDL2_image REQUIRED)
if (${SDL_IMAGE_FOUND})
	include_directories(${SDL_IMAGE_INCLUDE_DIRS})
	target_link_libraries(hydorah ${SDL_IMAGE_LIBRARIES})
endif ()

find_package(PhysFS REQUIRED)
if (${PHYSFS_FOUND})
	include_directories(${PHYSFS_INCLUDE_DIR})
	target_link_libraries(hydorah ${PHYSFS_LIBRARY})
endif ()

find_package(PNG REQUIRED)
if (${PNG_FOUND})
	include_directories(${PNG_INCLUDE_DIRS})
	target_link_libraries(hydorah ${PNG_LIBRARIES})
	add_definitions(${PNG_DEFINITIONS})
endif ()

if (${BUILD_TESTS})
	add_subdirectory("tests")
endif ()
