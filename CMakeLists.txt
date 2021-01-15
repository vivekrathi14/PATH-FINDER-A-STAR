cmake_minimum_required(VERSION 3.11)

# project name
project(a_star)

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)

# include header files
include_directories(include)

# source files
set(project_sources
    src/a_star.cpp
    src/main.cpp)

# create executable
add_executable(${PROJECT_NAME} ${project_sources})