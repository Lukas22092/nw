cmake_minimum_required(VERSION 3.10)
project(proj)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(OpenSSL REQUIRED)
add_executable(my_app
    src/main.cpp
    src/connection.cpp
    src/json_reader.cpp
    src/hypixel_connection.cpp
)

target_include_directories(my_app PRIVATE include)


target_link_libraries(my_app PRIVATE  PRIVATE OpenSSL::SSL OpenSSL::Crypto Boost::filesystem)
