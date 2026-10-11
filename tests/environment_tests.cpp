#include <iostream>
#include <vector>
#include "environment/Car.h"
#include "environment/Truck.h"
#include "environment/Motorcycle.h"
#include "environment/SafeZone.h"
#include "environment/EnvironmentEvent.h"
#include "player/AssaultPlayer.h"
#include "player/MedicPlayer.h"

static int checks = 0, failures = 0;
#define CHECK(c) do { ++checks; if (!(c)) { ++failures; std::cerr << "FAILED: " #c " at line " << __LINE__ << "\n"; } } while (0)

int main() {
    AssaultPlayer player(1, "TestPlayer", 100, 10, Position(0, 0, 0));
    Car car("Test Car", Position(0, 0, 0), 30, 100, 50);
    CHECK(car.getVehicleType() == "Car");
    CHECK(car.enter(player));
    CHECK(car.isOccupied());
    CHECK(!car.enter(player)); // already occupied
    CHECK(car.moveTo(Position(10, 0, 0)));
    CHECK(car.getPosition() == Position(10, 0, 0));
    CHECK(car.exit());
    CHECK(player.getPosition() == Position(10, 0, 0));
    CHECK(!car.isOccupied());

    Truck truck;
    Motorcycle bike;
    CHECK(truck.getVehicleType() == "Truck");
    CHECK(bike.getVehicleType() == "Motorcycle");
    CHECK(truck.getSpeed() < bike.getSpeed());

    SafeZone zone(Position(0, 0, 0), 20.0f, 5.0f, 5.0f, 10);
    CHECK(zone.contains(Position(10, 0, 0)));
    CHECK(!zone.contains(Position(21, 0, 0)));
    zone.shrink();
    CHECK(zone.getRadius() == 15.0f);
    MedicPlayer outside(2, "Outside", 100, 0, Position(30, 0, 0));
    CHECK(zone.applyOutsideDamage(outside) == 10);
    CHECK(outside.getHealth() == 90);
    CHECK(zone.applyOutsideDamage(player) == 0);
    zone.shrink(100.0f);
    CHECK(zone.getRadius() == 5.0f);

    EnvironmentEventLog log;
    log.record("ZONE_CHANGE", "The safe zone shrank.");
    log.record("ITEM_DISCOVERY", "A supply item was found.");
    CHECK(log.getEvents().size() == 2);
    log.clear();
    CHECK(log.getEvents().empty());

    std::cout << checks - failures << "/" << checks << " checks passed.\n";
    return failures == 0 ? 0 : 1;
}
