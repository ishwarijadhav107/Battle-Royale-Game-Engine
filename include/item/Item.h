#ifndef ITEM_H
#define ITEM_H

#include <string>

// Forward declaration.
// Player will be fully included in Item.cpp when needed.
class Player;

/**
 * @brief Types of items available in the Battle Royale game.
 */
enum class ItemType {
    Weapon,
    Armor,
    HealthPotion,
    PowerUp
};

/**
 * @brief Abstract base class for all inventory items.
 *
 * Demonstrates:
 * - Abstraction through pure virtual use()
 * - Inheritance through derived item classes
 * - Polymorphism through virtual functions
 * - Encapsulation through protected data and public getters
 */
class Item {
protected:
    std::string name;
    ItemType type;
    int value;

public:
    Item(const std::string& name, ItemType type, int value);
    virtual ~Item() = default;

    // Every item must define how it is used.
    virtual void use(Player& player) = 0;

    // Display information about the item.
    virtual void displayInfo() const;

    // Getters
    const std::string& getName() const;
    ItemType getType() const;
    int getValue() const;
};

#endif // ITEM_H
