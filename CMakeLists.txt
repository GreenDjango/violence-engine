#
## VE PROJECT, 2020
## VIOLENCE Engine
## File description:
## CMakeLists.txt
#

cmake_minimum_required(VERSION 3.11)
project(ve_client VERSION 0.1)

set(CMAKE_VERBOSE_MAKEFILE OFF)
if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable")
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
# https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_generator.html#cmake-targets-approach

# set projects path
set(CLIENT_PATH "${CMAKE_SOURCE_DIR}/client")

# include headers
include_directories(
	${CLIENT_PATH}
	"${CMAKE_SOURCE_DIR}"
)

# client files
FILE(GLOB_RECURSE CLIENT_SRC
	"${CLIENT_PATH}/*"
)

add_executable(ve_client
	${CLIENT_SRC}
)

# client link
target_link_libraries(ve_client
	${CONAN_LIBS}
)

file(COPY ${CMAKE_SOURCE_DIR}/client/assets
     DESTINATION ${CMAKE_BINARY_DIR}/bin)
