// Experimental evaluation for the Weapons & Combat module (Member 2).
//
// Experiment A: expected damage of every weapon at different distances.
// Experiment B: shots needed to eliminate a 100 HP (no shield) target at three ranges (2 m, 30 m, 100 m).
//
// Uses Weapon::expectedDamage() so the result is deterministic (crits are averaged).

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "weapon/Gun.h"
#include "weapon/MeleeWeapon.h"
#include "weapon/Shotgun.h"
#include "weapon/SniperRifle.h"

int main() {
    std::vector<std::unique_ptr<Weapon>> weapons;
    weapons.push_back(std::make_unique<Gun>("Pistol", 15, 30.0f, 12, 1.0f));
    weapons.push_back(std::make_unique<Gun>("Assault Rifle", 20, 60.0f, 30, 2.0f));
    weapons.push_back(std::make_unique<Shotgun>());
    weapons.push_back(std::make_unique<SniperRifle>());
    weapons.push_back(std::make_unique<MeleeWeapon>("Combat Knife", 35, 2.0f));

    const std::vector<float> distances = {1, 5, 10, 20, 40, 60, 100, 150};

    std::cout << "EXPERIMENT A - expected damage per shot vs distance ('-' = out of range)\n\n";
    std::cout << std::left << std::setw(16) << "Weapon";
    for (float d : distances) {
        std::cout << std::right << std::setw(7) << (std::to_string(static_cast<int>(d)) + "m");
    }
    std::cout << "\n" << std::string(16 + 7 * distances.size(), '-') << "\n";
    for (const auto& w : weapons) {
        std::cout << std::left << std::setw(16) << w->getName();
        for (float d : distances) {
            if (d > w->getRange()) {
                std::cout << std::right << std::setw(7) << "-";
            } else {
                std::cout << std::right << std::setw(7) << std::fixed << std::setprecision(1)
                          << w->expectedDamage(d);
            }
        }
        std::cout << "\n";
    }

    const std::vector<float> killDistances = {2, 30, 100};
    std::cout << "\n\nEXPERIMENT B - shots needed to eliminate a 100 HP target ('-' = out of range)\n\n";
    std::cout << std::left << std::setw(16) << "Weapon";
    for (float d : killDistances) {
        std::cout << std::right << std::setw(9) << (std::to_string(static_cast<int>(d)) + "m");
    }
    std::cout << "\n" << std::string(16 + 9 * killDistances.size(), '-') << "\n";
    for (const auto& w : weapons) {
        std::cout << std::left << std::setw(16) << w->getName();
        for (float d : killDistances) {
            if (d > w->getRange()) {
                std::cout << std::right << std::setw(9) << "-";
            } else {
                int shots = static_cast<int>(std::ceil(100.0f / w->expectedDamage(d)));
                std::cout << std::right << std::setw(9) << shots;
            }
        }
        std::cout << "\n";
    }

    std::cout << "\nObservations: the shotgun is the best close-range weapon but useless beyond 15m,\n"
                 "the rifle is the all-rounder, and the sniper dominates at range but is weak up close.\n";
    return 0;
}
