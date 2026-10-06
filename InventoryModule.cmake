# Inventory, Items & Power-ups module (Member 3).

add_library(InventoryLib STATIC
    src/item/Item.cpp
    src/item/WeaponItem.cpp
    src/item/ArmorItem.cpp
    src/item/HealthPotion.cpp
    src/item/PowerUp.cpp
    src/item/Inventory.cpp
)

target_link_libraries(InventoryLib PUBLIC PlayerLib WeaponLib)
