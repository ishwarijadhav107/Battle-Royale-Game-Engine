#ifndef WEAPON_ITEM_H
#define WEAPON_ITEM_H

#include "item/Item.h"

// Forward declarations
class Player;
class Weapon;

/**
 * @brief Inventory item that represents a weapon.
 *
 * Connects the Inventory/Item system with Member 2's Weapon system.
 * Demonstrates inheritance and association.
 */
class WeaponItem : public Item {
private:
    Weapon* weapon;   // Association with Member 2's Weapon class

public:
    WeaponItem(const std::string& name, Weapon* weapon);

    void use(Player& player) override;
    void displayInfo() const override;

    Weapon* getWeapon() const;
};

#endif // WEAPON_ITEM_H
