#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

#include "item/Item.h"

// Forward declaration
class Player;

/**
 * @brief Inventory item that restores player health.
 *
 * Demonstrates inheritance and polymorphism.
 */
class HealthPotion : public Item {
private:
    int healAmount;

public:
    HealthPotion(const std::string& name, int healAmount);

    void use(Player& player) override;
    void displayInfo() const override;

    int getHealAmount() const;
};

#endif // HEALTH_POTION_H
