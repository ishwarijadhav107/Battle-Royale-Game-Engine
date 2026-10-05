#include "weapon/MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(const std::string& name, int damage, float range)
    : Weapon(name, damage, range, 0) {}  // 0 ammo = no ammunition

int MeleeWeapon::calculateDamage(float /*distance*/) const {
    return damage;  // always full damage if the target is within reach
}

std::string MeleeWeapon::getWeaponType() const { return "Melee"; }
