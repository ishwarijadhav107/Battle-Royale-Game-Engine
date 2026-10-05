#include "weapon/Gun.h"

#include <algorithm>
#include <cmath>

Gun::Gun(const std::string& name, int damage, float range, int magazineSize)
    : Weapon(name, damage, range, magazineSize) {}

int Gun::calculateDamage(float distance) const {
    float falloffStart = range * 0.5f;
    if (distance <= falloffStart) {
        return damage;  // full damage up close
    }
    // Between half range and max range the damage drops linearly to 50%.
    float t = (distance - falloffStart) / (range - falloffStart);
    t = std::min(1.0f, t);
    return static_cast<int>(std::lround(damage * (1.0f - 0.5f * t)));
}

std::string Gun::getWeaponType() const { return "Gun"; }
