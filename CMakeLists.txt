cmake_minimum_required(VERSION 3.16)
project(Training)

set(CMAKE_CXX_STANDARD 20)

# Add all headers files under the include directory
include_directories(include inline)

# Add all c* source files under the src directory
file(GLOB_RECURSE SOURCES "src/*.c*")
add_executable(${PROJECT_NAME} ${SOURCES})

