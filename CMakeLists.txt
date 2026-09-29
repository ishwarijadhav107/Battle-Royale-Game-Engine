cmake_minimum_required(VERSION 3.15)
project(BattleRoyaleGameEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

enable_testing()

# ---------------------------------------------------------------------------
# Player Module (Member 1)
# ---------------------------------------------------------------------------
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
add_test(NAME PlayerTests COMMAND player_tests)

# ---------------------------------------------------------------------------
# Weapons & Combat Module (Member 2)
# ---------------------------------------------------------------------------
add_library(WeaponLib STATIC
    src/weapon/Weapon.cpp
    src/weapon/Gun.cpp
    src/weapon/Shotgun.cpp
    src/weapon/SniperRifle.cpp
    src/weapon/MeleeWeapon.cpp
    src/weapon/Loadout.cpp
)
target_link_libraries(WeaponLib PUBLIC PlayerLib)

# Unit Tests for the Weapons & Combat System
add_executable(weapon_tests tests/weapon_tests.cpp)
target_link_libraries(weapon_tests PRIVATE WeaponLib)
add_test(NAME WeaponTests COMMAND weapon_tests)

# Live demo, extensibility demo and experiments
add_executable(weapons_demo examples/weapons_demo.cpp)
target_link_libraries(weapons_demo PRIVATE WeaponLib)

add_executable(extensibility_demo examples/extensibility_demo.cpp)
target_link_libraries(extensibility_demo PRIVATE WeaponLib)

add_executable(damage_experiment experiments/damage_experiment.cpp)
target_link_libraries(damage_experiment PRIVATE WeaponLib)
