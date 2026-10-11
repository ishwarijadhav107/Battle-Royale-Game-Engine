#include "environment/Car.h"
Car::Car(const std::string& name, const Position& position, float speed, int durability, float fuel)
    : Vehicle(name, position, speed, durability, fuel) {}
std::string Car::getVehicleType() const { return "Car"; }
