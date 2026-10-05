#include "item/ArmorItem.h"
#include "player/Player.h"

#include <iostream>

ArmorItem::ArmorItem(const std::string& name, int armorValue)
    : Item(name, ItemType::Armor, armorValue),
      armorValue(armorValue) {
}

void ArmorItem::use(Player& player) {
    if (armorValue <= 0) {
        std::cout << "Invalid armor value." << std::endl;
        return;
    }

    int newShield = player.getShield() + armorValue;

    if (newShield > player.getMaxShield()) {
        newShield = player.getMaxShield();
    }

    player.setShield(newShield);

    std::cout << player.getName()
              << " used " << name
              << " and now has "
              << newShield << " shield."
              << std::endl;
}

void ArmorItem::displayInfo() const {
    Item::displayInfo();

    std::cout << "Armor Value: "
              << armorValue
              << std::endl;
}

int ArmorItem::getArmorValue() const {
    return armorValue;
}
