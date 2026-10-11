#ifndef TRUCK_H
#define TRUCK_H
#include "environment/Vehicle.h"

class Truck : public Vehicle {
public:
    explicit Truck(const std::string& name = "Armored Truck",
                   const Position& position = Position(),
                   float speed = 22.0f, int durability = 250, float fuel = 140.0f);
    std::string getVehicleType() const override;
protected:
    float fuelCost(float distance) const override;
};
#endif
