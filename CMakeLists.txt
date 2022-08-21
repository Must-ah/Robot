cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Robot VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
list(APPEND EXTRA_LIBS src)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")

add_executable(Robot main.cpp)

target_link_libraries(Robot PUBLIC ${EXTRA_LIBS})

target_include_directories(Robot PUBLIC
    "${PROJECT_BINARY_DIR}"
    ${EXTRA_INCLUDES}
)