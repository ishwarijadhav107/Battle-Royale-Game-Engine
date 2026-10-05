#ifndef POWER_UP_H
#define POWER_UP_H

#include "item/Item.h"

// Forward declaration
class Player;

/**
 * @brief Inventory item that provides a temporary power-up effect.
 *
 * Demonstrates inheritance and polymorphism.
 */
class PowerUp : public Item {
private:
    int powerValue;

public:
    PowerUp(const std::string& name, int powerValue);

    void use(Player& player) override;
    void displayInfo() const override;

    int getPowerValue() const;
};

#endif // POWER_UP_H
