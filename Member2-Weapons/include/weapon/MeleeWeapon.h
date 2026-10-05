#ifndef MELEE_WEAPON_H
#define MELEE_WEAPON_H

#include "weapon/Weapon.h"

// Close-combat weapon (knife, axe ...): no ammo, no reload, very short range.
class MeleeWeapon : public Weapon {
public:
    MeleeWeapon(const std::string& name = "Combat Knife", int damage = 35, float range = 2.0f);

    int calculateDamage(float distance) const override;
    std::string getWeaponType() const override;
};

#endif // MELEE_WEAPON_H
