#include "item/PowerUp.h"
#include "player/Player.h"

#include <iostream>

PowerUp::PowerUp(const std::string& name, int powerValue)
    : Item(name, ItemType::PowerUp, powerValue),
      powerValue(powerValue) {
}

void PowerUp::use(Player& player) {
    if (powerValue <= 0) {
        std::cout << "Invalid power-up value." << std::endl;
        return;
    }

    int newShield = player.getShield() + powerValue;

    if (newShield > player.getMaxShield()) {
        newShield = player.getMaxShield();
    }

    player.setShield(newShield);

    std::cout << player.getName()
              << " used " << name
              << " and received a power-up effect."
              << std::endl;
}

void PowerUp::displayInfo() const {
    Item::displayInfo();

    std::cout << "Power Value: "
              << powerValue
              << std::endl;
}
int PowerUp::getPowerValue() const {
    return powerValue;
}
