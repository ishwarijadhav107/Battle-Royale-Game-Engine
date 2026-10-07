#include <iostream>

#include "player/AssaultPlayer.h"
#include "weapon/Gun.h"

#include "item/ArmorItem.h"
#include "item/HealthPotion.h"
#include "item/Inventory.h"
#include "item/PowerUp.h"
#include "item/WeaponItem.h"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   BATTLE ROYALE - INVENTORY DEMO" << std::endl;
    std::cout << "   Member 3: Inventory, Items & Power-ups" << std::endl;
    std::cout << "========================================" << std::endl;

    // Create a player using Member 1's existing Player system.
    AssaultPlayer player(
        1,
        "DemoPlayer",
        100,
        0,
        Position(0, 0, 0)
    );

    // Create Member 3's inventory.
    Inventory inventory;

    // Create Member 2's weapon.
    Gun gun("Rifle", 20, 60.0f, 30);

    // Create different inventory items.
    ArmorItem* armor = new ArmorItem("Level 2 Armor", 25);
    HealthPotion* potion = new HealthPotion("Health Potion", 30);
    PowerUp* powerUp = new PowerUp("Shield Boost", 20);
    WeaponItem* weaponItem = new WeaponItem("Rifle", &gun);

    // Add items to the inventory.
    inventory.addItem(armor);
    inventory.addItem(potion);
    inventory.addItem(powerUp);
    inventory.addItem(weaponItem);

    std::cout << "\n--- Initial Player Status ---" << std::endl;
    player.displayStatus();

    std::cout << "\n--- Inventory Contents ---" << std::endl;
    inventory.displayInventory();

    std::cout << "\n--- Using Armor ---" << std::endl;
    inventory.useItem(0, player);
    player.displayStatus();

    std::cout << "\n--- Damaging Player ---" << std::endl;
    player.takeDamage(50);
    player.displayStatus();

    std::cout << "\n--- Using Health Potion ---" << std::endl;
    inventory.useItem(1, player);
    player.displayStatus();

    std::cout << "\n--- Using Power-up ---" << std::endl;
    inventory.useItem(2, player);
    player.displayStatus();

    std::cout << "\n--- Selecting Weapon ---" << std::endl;
    inventory.useItem(3, player);

    std::cout << "\n--- Final Inventory ---" << std::endl;
    inventory.displayInventory();

    std::cout << "\nTotal items in inventory: "
              << inventory.getItemCount()
              << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "Inventory demo completed successfully." << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
