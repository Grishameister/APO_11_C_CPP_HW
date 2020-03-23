FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES("${GTEST_INCLUDE_DIRS}")

FIND_PACKAGE(Threads REQUIRED)

set(test_name project_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${includes})

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")

add_executable(${test_name} ${tests})

target_link_libraries(${test_name} ${library_name} gtest_main gtest -lpthread -lm)

add_test(NAME ${test_name} COMMAND ${test_name})
