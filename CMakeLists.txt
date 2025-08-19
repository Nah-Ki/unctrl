cmake_minimum_required(VERSION 3.10)
project(NetworkedGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(client
    src/client/client_main.cpp
    src/shared/packets.hpp
)
target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-network)

add_executable(server
    src/server/server_main.cpp
    src/shared/packets.hpp
)
target_link_libraries(server sfml-network sfml-system)

