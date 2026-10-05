#include "item/WeaponItem.h"
#include "weapon/Weapon.h"
#include "player/Player.h"
#include <iostream>

WeaponItem::WeaponItem(const std::string& name, Weapon* weapon)
    : Item(name, ItemType::Weapon, 0), weapon(weapon) {
}

void WeaponItem::use(Player& player) {
    if (weapon != nullptr) {
        std::cout << player.getName() << " selected weapon: "
                  << weapon->getName() << std::endl;
    }
}

void WeaponItem::displayInfo() const {
    Item::displayInfo();

    if (weapon != nullptr) {
        std::cout << "Weapon: " << weapon->getName() << std::endl;
    }
}

Weapon* WeaponItem::getWeapon() const {
    return weapon;
}
