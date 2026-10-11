#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include "environment/Vehicle.h"

class Motorcycle : public Vehicle {
public:
    explicit Motorcycle(const std::string& name = "Off-road Bike",
                        const Position& position = Position(),
                        float speed = 45.0f, int durability = 80, float fuel = 70.0f);
    std::string getVehicleType() const override;
protected:
    float fuelCost(float distance) const override;
};
#endif
