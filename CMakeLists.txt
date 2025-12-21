cmake_minimum_required(VERSION 3.10)
project(proj)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost REQUIRED COMPONENTS filesystem)

add_executable(my_app
    src/main.cpp
    include/test.cpp
)

target_include_directories(my_app PRIVATE include)

target_link_libraries(my_app PRIVATE Boost::filesystem)
