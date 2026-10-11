#include <iostream>
#include <vector>
#include "environment/Car.h"
#include "environment/Truck.h"
#include "environment/Motorcycle.h"
#include "environment/SafeZone.h"
#include "environment/EnvironmentEvent.h"
#include "player/AssaultPlayer.h"
#include "player/MedicPlayer.h"

int main() {
    AssaultPlayer player(1, "Rex", 100, 20, Position(0, 0, 0));
    MedicPlayer teammate(2, "Mira", 100, 20, Position(2, 0, 0));
    Car car("Battle Car", Position(0, 0, 0));
    Truck truck;
    Motorcycle bike;

    std::cout << "--- Vehicle types ---\n";
    car.displayInfo(); truck.displayInfo(); bike.displayInfo();

    std::cout << "\n--- Enter, move, exit ---\n";
    if (car.enter(player)) {
        car.moveTo(Position(25, 0, 0));
        car.exit();
    }

    std::cout << "\n--- Safe zone ---\n";
    SafeZone zone(Position(0, 0, 0), 20.0f, 5.0f, 5.0f, 15);
    zone.displayInfo();
    zone.shrink();
    zone.applyOutsideDamage(player);
    std::vector<Player*> players{&player, &teammate};
    zone.applyOutsideDamage(players);

    std::cout << "\n--- Environment events ---\n";
    EnvironmentEventLog events;
    events.record("ZONE_CHANGE", "Safe zone radius decreased.");
    events.record("ITEM_DISCOVERY", "A health potion was discovered at (10, 0, 0).");
    events.record("PLAYER_ELIMINATION", "A player was eliminated.");
    events.displayEvents();
    return 0;
}
