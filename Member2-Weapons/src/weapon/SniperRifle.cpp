#include "weapon/SniperRifle.h"

#include <algorithm>
#include <cmath>
#include <iostream>

SniperRifle::SniperRifle(const std::string& name, int damage, float range, int magazineSize,
                         float critChance, float critMultiplier, float minRange)
    : Weapon(name, damage, range, magazineSize),
      critChance(std::max(0.0f, std::min(1.0f, critChance))),
      critMultiplier(std::max(1.0f, critMultiplier)),
      minRange(std::max(0.0f, minRange)),
      rng(std::random_device{}()) {}

int SniperRifle::calculateDamage(float distance) const {
    double result = damage;
    if (distance < minRange) {
        result *= 0.4;  // too close: only 40% damage
    }
    std::uniform_real_distribution<double> roll(0.0, 1.0);
    if (roll(rng) < critChance) {
        result *= critMultiplier;  // critical hit
    }
    return static_cast<int>(std::lround(result));
}

std::string SniperRifle::getWeaponType() const { return "Sniper"; }

void SniperRifle::displayInfo() const {
    Weapon::displayInfo();
    std::cout << "  Crit  : " << static_cast<int>(critChance * 100) << "% chance, x"
              << critMultiplier << " damage\n"
              << "  Weak below " << minRange << " range (40% damage)\n";
}

float SniperRifle::getCritChance() const { return critChance; }
void SniperRifle::setCritChance(float chance) { critChance = std::max(0.0f, std::min(1.0f, chance)); }
