#ifndef ARMOR_ITEM_H
#define ARMOR_ITEM_H

#include "item/Item.h"

// Forward declaration
class Player;

/**
 * @brief Inventory item that represents armor.
 *
 * Provides shield protection to the player.
 * Demonstrates inheritance and polymorphism.
 */
class ArmorItem : public Item {
private:
    int armorValue;

public:
    ArmorItem(const std::string& name, int armorValue);

    void use(Player& player) override;
    void displayInfo() const override;

    int getArmorValue() const;
};

#endif // ARMOR_ITEM_H
