cmake_minimum_required (VERSION 2.8)
project (OpenHydorah)

add_subdirectory(hyd_engine)

set (SRC_LIST main.d game.d intro.d main_menu.d player.d projectile.d enemy.d weapon.d)

foreach (i ${SRC_LIST})
	set (SRC "${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/src/${i}")
endforeach(i)

set (D_FLAGS "-I${CMAKE_CURRENT_SOURCE_DIR}/hyd_engine/bindings/D -I${CMAKE_CURRENT_SOURCE_DIR}/src -L-L${CMAKE_CURRENT_BINARY_DIR}/hyd_engine -L-lhyd -L-R${CMAKE_CURRENT_BINARY_DIR}/hyd_engine")
set (BUILD_SCRIPT "dmd -g ${D_FLAGS}  -odobj -ofhydorah ${SRC}")
set (RUN_SCRIPT "rdmd ${D_FLAGS} ${SRC}")

file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/build.sh ${BUILD_SCRIPT})
file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/run.sh ${RUN_SCRIPT})

if (VOGL_PATH)
	set(VOGL_SCRIPT "#!/bin/bash\nexport LD_PRELOAD=${VOGL_PATH}/libvogltrace64.so\n${VOGL_PATH}/vogleditor64")
	file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/vogl.sh ${VOGL_SCRIPT})
endif()
