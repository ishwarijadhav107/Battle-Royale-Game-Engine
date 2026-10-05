#ifndef SNIPER_RIFLE_H
#define SNIPER_RIFLE_H

#include <random>

#include "weapon/Weapon.h"

// Long-range weapon: high damage, small magazine, chance of a critical hit,
// but only 40% damage when the target is closer than minRange.
class SniperRifle : public Weapon {
private:
    float critChance;      // 0.0 to 1.0
    float critMultiplier;  // damage multiplier on a critical hit
    float minRange;        // closer than this = reduced damage
    mutable std::mt19937 rng;

public:
    SniperRifle(const std::string& name = "Sniper Rifle", int damage = 60,
                float range = 150.0f, int magazineSize = 5,
                float critChance = 0.2f, float critMultiplier = 1.5f,
                float minRange = 20.0f);

    int calculateDamage(float distance) const override;
    std::string getWeaponType() const override;
    void displayInfo() const override;

    float getCritChance() const;
    void setCritChance(float chance);
};

#endif // SNIPER_RIFLE_H
