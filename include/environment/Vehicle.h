#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "player/Player.h"

/**
 * Abstract vehicle associated with one player at a time.
 * Vehicle movement updates the vehicle position; the player's position is
 * synchronized when the player exits.
 */
class Vehicle {
protected:
    std::string name;
    Position position;
    float speed;
    int durability;
    int maxDurability;
    float fuel;
    float maxFuel;
    Player* occupant; // association; Vehicle does not own the Player

    virtual float fuelCost(float distance) const;

public:
    Vehicle(const std::string& name, const Position& position,
            float speed, int durability, float fuel);
    virtual ~Vehicle() = default;

    virtual std::string getVehicleType() const = 0;
    virtual void displayInfo() const;

    bool enter(Player& player);
    bool exit();
    bool moveTo(const Position& destination);
    bool refuel(float amount);
    void takeDamage(int amount);
    bool repair(int amount);

    const std::string& getName() const;
    Position getPosition() const;
    float getSpeed() const;
    int getDurability() const;
    float getFuel() const;
    bool isOccupied() const;
    Player* getOccupant() const;
    bool isOperational() const;
};

#endif
