#include "item/HealthPotion.h"
#include "player/Player.h"

#include <iostream>

HealthPotion::HealthPotion(const std::string& name, int healAmount)
    : Item(name, ItemType::HealthPotion, healAmount),
      healAmount(healAmount) {
}

void HealthPotion::use(Player& player) {
    if (healAmount <= 0) {
        std::cout << "Invalid healing amount." << std::endl;
        return;
    }

    int newHealth = player.getHealth() + healAmount;

    if (newHealth > player.getMaxHealth()) {
        newHealth = player.getMaxHealth();
    }

    player.setHealth(newHealth);

    std::cout << player.getName()
              << " used " << name
              << " and now has "
              << newHealth << " health."
              << std::endl;
}

void HealthPotion::displayInfo() const {
    Item::displayInfo();

    std::cout << "Heal Amount: "
              << healAmount
              << std::endl;
}

int HealthPotion::getHealAmount() const {
    return healAmount;
}
