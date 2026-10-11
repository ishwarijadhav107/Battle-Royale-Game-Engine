#include "environment/Vehicle.h"
#include <algorithm>
#include <iostream>

Vehicle::Vehicle(const std::string& name, const Position& position,
                 float speed, int durability, float fuel)
    : name(name), position(position), speed(std::max(0.0f, speed)),
      durability(std::max(0, durability)), maxDurability(std::max(0, durability)),
      fuel(std::max(0.0f, fuel)), maxFuel(std::max(0.0f, fuel)), occupant(nullptr) {}

float Vehicle::fuelCost(float distance) const { return distance; }

bool Vehicle::enter(Player& player) {
    if (!isOperational() || occupant != nullptr || !player.isAlive()) return false;
    if (player.getPosition().distanceTo(position) > 5.0f) return false;
    occupant = &player;
    std::cout << player.getName() << " entered " << name << ".\n";
    return true;
}

bool Vehicle::exit() {
    if (!occupant) return false;
    occupant->setPosition(position);
    std::cout << occupant->getName() << " exited " << name << " at " << position << ".\n";
    occupant = nullptr;
    return true;
}

bool Vehicle::moveTo(const Position& destination) {
    if (!isOperational() || !occupant || !occupant->isAlive()) return false;
    float distance = position.distanceTo(destination);
    if (distance <= 0.0f) return true;
    float cost = fuelCost(distance);
    if (fuel < cost) return false;
    fuel -= cost;
    position = destination;
    return true;
}

bool Vehicle::refuel(float amount) {
    if (amount <= 0.0f || fuel >= maxFuel) return false;
    fuel = std::min(maxFuel, fuel + amount);
    return true;
}

void Vehicle::takeDamage(int amount) {
    if (amount <= 0 || durability <= 0) return;
    durability = std::max(0, durability - amount);
    if (durability == 0) {
        if (occupant) exit();
        std::cout << name << " has been destroyed.\n";
    }
}

bool Vehicle::repair(int amount) {
    if (amount <= 0 || durability <= 0 || durability >= maxDurability) return false;
    durability = std::min(maxDurability, durability + amount);
    return true;
}

void Vehicle::displayInfo() const {
    std::cout << "=== " << getVehicleType() << ": " << name << " ===\n"
              << "Position: " << position << "\nSpeed: " << speed
              << "\nDurability: " << durability << "/" << maxDurability
              << "\nFuel: " << fuel << "/" << maxFuel
              << "\nOccupant: " << (occupant ? occupant->getName() : "none") << "\n";
}
const std::string& Vehicle::getName() const { return name; }
Position Vehicle::getPosition() const { return position; }
float Vehicle::getSpeed() const { return speed; }
int Vehicle::getDurability() const { return durability; }
float Vehicle::getFuel() const { return fuel; }
bool Vehicle::isOccupied() const { return occupant != nullptr; }
Player* Vehicle::getOccupant() const { return occupant; }
bool Vehicle::isOperational() const { return durability > 0; }
