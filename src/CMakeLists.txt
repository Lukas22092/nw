add_executable(main_app main.cpp)

target_link_libraries(main_app connection.cpp hypixel_connection.cpp json_reader.cpp PRIVATE include)
