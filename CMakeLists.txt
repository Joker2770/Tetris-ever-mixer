cmake_minimum_required(VERSION 2.8.12)

project(Tetris-ever-mixer)
set(CMAKE_C_FLAGS, "-Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "My multi config types" FORCE)
elseif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RELEASE)
endif()

if(UNIX)
	find_package( PkgConfig REQUIRED )
	pkg_check_modules( sdl2 REQUIRED IMPORTED_TARGET sdl2 )
	pkg_check_modules( SDL2_ttf REQUIRED IMPORTED_TARGET SDL2_ttf )
	pkg_check_modules( SDL2_mixer REQUIRED IMPORTED_TARGET SDL2_mixer )
endif()

include_directories(
	${CMAKE_SOURCE_DIR}
	${SDL2_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIR}
)
set(Tetris_SRCS
	"${CMAKE_SOURCE_DIR}/src/main.c"
	"${CMAKE_SOURCE_DIR}/src/tetris.c"
)
add_executable(${PROJECT_NAME} ${Tetris_SRCS})

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::sdl2 )
	target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_ttf )
	target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_mixer )
endif()

if(UNIX)
	set(CMAKE_INSTALL_PREFIX /usr/local)
	install(TARGETS ${PROJECT_NAME} DESTINATION bin)
	install(FILES res/bb3273.ttf DESTINATION bin)
	install(FILES res/tetrisb.mid DESTINATION bin)
elseif(WIN32)
	set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/")
	install(TARGETS ${PROJECT_NAME} DESTINATION bin)
	install(FILES res/bb3273.ttf DESTINATION bin)
	install(FILES res/tetrisb.mid DESTINATION bin)
endif()
