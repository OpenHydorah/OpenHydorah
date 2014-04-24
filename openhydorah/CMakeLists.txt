cmake_minimum_required(VERSION 2.8)
project (OpenHydorah)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

include_directories(include)
set (SRC src/main.c src/init.c src/cleanup.c)

add_executable(hydorah ${SRC})

find_package(SDL2 REQUIRED)
if (${SDL_FOUND})
	include_directories(${SDL_INCLUDE_DIR})
	target_link_libraries(hydorah ${SDL_LIBRARY})
endif ()

find_package(PhysFS REQUIRED)
if (${PHYSFS_FOUND})
	include_directories(${PHYSFS_INCLUDE_DIR})
	target_link_libraries(hydorah ${PHYSFS_LIBRARY})
endif ()
