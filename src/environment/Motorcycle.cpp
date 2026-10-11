#include "environment/Motorcycle.h"
Motorcycle::Motorcycle(const std::string& name, const Position& position, float speed, int durability, float fuel)
    : Vehicle(name, position, speed, durability, fuel) {}
std::string Motorcycle::getVehicleType() const { return "Motorcycle"; }
float Motorcycle::fuelCost(float distance) const { return distance * 0.65f; }
