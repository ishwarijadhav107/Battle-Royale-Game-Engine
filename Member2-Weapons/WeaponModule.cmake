# Weapons module (Member 2).
# Add this ONE line to the root CMakeLists.txt, after the PlayerLib target:
#     include(WeaponModule.cmake)

add_library(WeaponLib STATIC
    src/weapon/Weapon.cpp
    src/weapon/Gun.cpp
    src/weapon/SniperRifle.cpp
    src/weapon/MeleeWeapon.cpp
    src/weapon/Loadout.cpp
)
target_link_libraries(WeaponLib PUBLIC PlayerLib)

enable_testing()
add_executable(weapon_tests tests/weapon_tests.cpp)
target_link_libraries(weapon_tests PRIVATE WeaponLib)
add_test(NAME WeaponTests COMMAND weapon_tests)

add_executable(weapons_demo tests/weapons_demo.cpp)
target_link_libraries(weapons_demo PRIVATE WeaponLib)
