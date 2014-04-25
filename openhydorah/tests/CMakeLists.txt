file(GLOB SRC tests_main.c ../src/refptr.c)

add_executable(hydorah_tests ${SRC})

find_package(Check REQUIRED)
if(${CHECK_FOUND})
	include_directories(${CHECK_INCLUDE_DIRS})
	target_link_libraries(hydorah_tests ${CHECK_LIBRARIES} -lpthread)
endif ()
