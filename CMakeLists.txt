cmake_minimum_required(VERSION 3.21)
project(data_structs_visualisations)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_MODULE_PATH "/Users/Home/SFML-2.2-osx-clang-universal/cmake/Modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(.)
include_directories(dsv)
include_directories(dsv/AnimatedSprite)

add_executable(data_structs_visualisations
        dsv/AnimatedSprite/AnimatedSprite.cpp
        dsv/AnimatedSprite/AnimatedSprite.hpp
        dsv/AnimatedSprite/Animation.cpp
        dsv/AnimatedSprite/Animation.hpp
        dsv/deque.h
        dsv/queue.h
        dsv/stack.h
        dsv/tree.h
        dsv/utils.h
        dsv/visualizer.h
        main.cpp)

target_link_libraries(data_structs_visualisations sfml-graphics sfml-audio)