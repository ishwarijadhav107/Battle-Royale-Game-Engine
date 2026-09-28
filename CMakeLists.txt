cmake_minimum_required(VERSION 3.15)
project(BattleRoyaleGameEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Player Module (Member 1)
add_library(PlayerLib STATIC
    src/player/Player.cpp
    src/player/AssaultPlayer.cpp
    src/player/SniperPlayer.cpp
    src/player/MedicPlayer.cpp
)

# Unit Tests for Player Management System
add_executable(player_tests
    tests/player_tests.cpp
)

target_link_libraries(player_tests PRIVATE PlayerLib)

enable_testing()
add_test(NAME PlayerTests COMMAND player_tests)
