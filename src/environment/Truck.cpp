#include "environment/Truck.h"
Truck::Truck(const std::string& name, const Position& position, float speed, int durability, float fuel)
    : Vehicle(name, position, speed, durability, fuel) {}
std::string Truck::getVehicleType() const { return "Truck"; }
float Truck::fuelCost(float distance) const { return distance * 1.25f; }
