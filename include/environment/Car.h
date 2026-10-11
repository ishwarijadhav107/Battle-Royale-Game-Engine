#ifndef CAR_H
#define CAR_H
#include "environment/Vehicle.h"

class Car : public Vehicle {
public:
    explicit Car(const std::string& name = "Battle Car",
                 const Position& position = Position(),
                 float speed = 35.0f, int durability = 150, float fuel = 100.0f);
    std::string getVehicleType() const override;
};
#endif
