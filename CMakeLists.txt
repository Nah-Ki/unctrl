cmake_minimum_required(VERSION 3.10)
project(unctrl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Shared source files
set(SHARED_SOURCES
    src/shared/game.cpp
    src/shared/player.cpp
    src/shared/game_state.cpp  # <-- also include this file if needed
)

# Client build
add_executable(client
    src/client/client_main.cpp
    src/client/net.cpp
    ${SHARED_SOURCES}
)
target_include_directories(client PRIVATE include src/shared)

# Server build
add_executable(server
    src/server/server_main.cpp
    src/server/net.cpp
    ${SHARED_SOURCES}
)
target_include_directories(server PRIVATE include src/shared)

