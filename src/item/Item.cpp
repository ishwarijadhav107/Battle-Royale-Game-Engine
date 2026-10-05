#include "item/Item.h"
#include <iostream>

Item::Item(const std::string& name, ItemType type, int value)
    : name(name), type(type), value(value) {
}

void Item::displayInfo() const {
    std::cout << "Item: " << name << std::endl;
    std::cout << "Value: " << value << std::endl;

    std::cout << "Type: ";

    switch (type) {
        case ItemType::Weapon:
            std::cout << "Weapon";
            break;

        case ItemType::Armor:
            std::cout << "Armor";
            break;

        case ItemType::HealthPotion:
            std::cout << "Health Potion";
            break;

        case ItemType::PowerUp:
            std::cout << "Power-Up";
            break;
    }

    std::cout << std::endl;
}

const std::string& Item::getName() const {
    return name;
}

ItemType Item::getType() const {
    return type;
}

int Item::getValue() const {
    return value;
}
