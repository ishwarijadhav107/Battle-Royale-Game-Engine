#ifndef GUN_H
#define GUN_H

#include "weapon/Weapon.h"

// Normal firearm (rifle, pistol ...). Medium range, uses a magazine.
// Full damage up to half of its range, then damage drops to 50% at maximum range.
class Gun : public Weapon {
public:
    Gun(const std::string& name = "Assault Rifle", int damage = 20,
        float range = 60.0f, int magazineSize = 30);

    int calculateDamage(float distance) const override;
    std::string getWeaponType() const override;
};

#endif // GUN_H
