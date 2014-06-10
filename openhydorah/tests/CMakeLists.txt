set(SRC tests_main.c tests_list.c tests_texture.c tests_entity.c tests_sprite.c tests_property.c
	tests_collision.c)
set(OH_SRC ../src/list.c ../src/texture.c ../src/filesystem.c ../src/entity.c ../src/vector.c
	../src/sprite.c ../src/frame.c ../src/animation.c ../src/property.c ../src/collision.c)

include_directories(../include)

add_executable(hydorah_tests ${OH_SRC} ${SRC})
target_link_libraries(hydorah_tests jansson -lm)

find_package(Check REQUIRED)
if(${CHECK_FOUND})
	include_directories(${CHECK_INCLUDE_DIRS})
	target_link_libraries(hydorah_tests ${CHECK_LIBRARIES} -lpthread)
endif ()

find_package(SDL2 REQUIRED)
if (${SDL_FOUND})
	include_directories(${SDL_INCLUDE_DIR})
	target_link_libraries(hydorah_tests ${SDL_LIBRARY})
endif ()

find_package(SDL2_image REQUIRED)
if (${SDL_IMAGE_FOUND})
	include_directories(${SDL_IMAGE_INCLUDE_DIRS})
	target_link_libraries(hydorah_tests ${SDL_IMAGE_LIBRARIES})
endif ()

find_package(PhysFS REQUIRED)
if (${PHYSFS_FOUND})
	include_directories(${PHYSFS_INCLUDE_DIR})
	target_link_libraries(hydorah_tests ${PHYSFS_LIBRARY})
endif ()

