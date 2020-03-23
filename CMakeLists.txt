cmake_minimum_required(VERSION 3.1)

set(project_name hw-2)
project(${project_name})

set(CMAKE_C_FLAGS "-g -Wall -Wextra -Werror -Wpedantic -pthread")
set(CMAKE_C_STANDARD 11)


if(ENABLE_PARALLEL)
	add_library(${project_name}parallel_lib SHARED ${PROJECT_SOURCE_DIR}/parallel_lib/src/utils.c)
	set(includes ${PROJECT_SOURCE_DIR}/parallel_lib/include)
	set(library_name ${project_name}parallel_lib)
	set(libsources ${PROJECT_SOURCE_DIR}/parallel_lib/src)
else()
	add_library(${project_name}consistent_lib STATIC ${PROJECT_SOURCE_DIR}/consistent_lib/src/utils.c)
	set(includes ${PROJECT_SOURCE_DIR}/consistent_lib/include)
	set(library_name ${project_name}consistent_lib)
	set(libsources ${PROJECT_SOURCE_DIR}/consistent_lib/src)
endif()

if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
endif()

include_directories(${includes})

enable_testing()
add_subdirectory(googletest)
add_subdirectory(test)


add_executable(${project_name} main.c)


target_link_libraries(${project_name} ${library_name})

