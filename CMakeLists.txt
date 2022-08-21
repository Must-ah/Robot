cmake_minimum_required(VERSION 3.10)

# set the project name and version
# project(Robot VERSION 1.0)
project(Robot VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
# add_subdirectory(tests)
list(APPEND EXTRA_LIBS src)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")

#add_executable(Robot main.cpp)
add_executable(Robot test.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# add_executable(tests test.cpp)

target_link_libraries(Robot PUBLIC 
${EXTRA_LIBS}
${GTEST_LIBRARIES}
pthread
)

target_include_directories(Robot PUBLIC
    "${PROJECT_BINARY_DIR}"
    ${EXTRA_INCLUDES}
)