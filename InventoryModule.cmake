# Inventory, Items & Power-ups module (Member 3).
# Add this line to the root CMakeLists.txt, AFTER the PlayerLib and
# WeaponModule.cmake lines (InventoryLib links to both):
#     include(InventoryModule.cmake)

add_library(InventoryLib STATIC
    src/item/Item.cpp
    src/item/WeaponItem.cpp
    src/item/ArmorItem.cpp
    src/item/HealthPotion.cpp
    src/item/PowerUp.cpp
    src/item/Inventory.cpp
)
target_link_libraries(InventoryLib PUBLIC PlayerLib WeaponLib)

enable_testing()
add_executable(inventory_tests tests/inventory_tests.cpp)
target_link_libraries(inventory_tests PRIVATE InventoryLib)
add_test(NAME InventoryTests COMMAND inventory_tests)
