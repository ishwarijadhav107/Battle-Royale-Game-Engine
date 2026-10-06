#include "item/Inventory.h"
#include "item/Item.h"
#include "player/Player.h"

#include <iostream>

Inventory::~Inventory() {
    for (Item* item : items) {
        delete item;
    }
    items.clear();
}

void Inventory::addItem(Item* item) {
    if (item != nullptr) {
        items.push_back(item);
    }
}

bool Inventory::removeItem(Item* item) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (*it == item) {
            items.erase(it);
            return true;
        }
    }

    return false;
}

Item* Inventory::getItem(int index) const {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        return nullptr;
    }

    return items[index];
}

int Inventory::getItemCount() const {
    return static_cast<int>(items.size());
}

void Inventory::displayInventory() const {
    if (items.empty()) {
        std::cout << "Inventory is empty." << std::endl;
        return;
    }

    std::cout << "Inventory:" << std::endl;

    for (int i = 0; i < static_cast<int>(items.size()); ++i) {
        std::cout << i + 1 << ". ";
        items[i]->displayInfo();
    }
}

void Inventory::useItem(int index, Player& player) {
    Item* item = getItem(index);

    if (item == nullptr) {
        std::cout << "Invalid inventory item." << std::endl;
        return;
    }

    item->use(player);
}
