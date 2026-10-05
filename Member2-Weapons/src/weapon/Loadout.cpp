#include "weapon/Loadout.h"

#include <iostream>
#include <utility>

Loadout::Loadout(Player* owner) : owner(owner), primaryActive(true) {}

void Loadout::equipPrimary(std::unique_ptr<Weapon> weapon) { primary = std::move(weapon); }
void Loadout::equipSecondary(std::unique_ptr<Weapon> weapon) { secondary = std::move(weapon); }

bool Loadout::switchWeapon() {
    if (primaryActive && secondary) {
        primaryActive = false;
        return true;
    }
    if (!primaryActive && primary) {
        primaryActive = true;
        return true;
    }
    return false;
}

Weapon* Loadout::getActiveWeapon() const {
    Weapon* wanted = primaryActive ? primary.get() : secondary.get();
    if (wanted) {
        return wanted;
    }
    return primaryActive ? secondary.get() : primary.get();  // fall back to the other slot
}

AttackResult Loadout::attack(Player* target) {
    Weapon* weapon = getActiveWeapon();
    if (owner && target && weapon) {
        return weapon->attack(*owner, *target);
    }
    AttackResult result;
    result.message = "Attack not possible (missing owner, target or weapon).";
    std::cout << "[Loadout] " << result.message << "\n";
    return result;
}

bool Loadout::reload() {
    Weapon* weapon = getActiveWeapon();
    return weapon && weapon->reload();
}

void Loadout::displayLoadout() const {
    std::cout << "--- Loadout of " << (owner ? owner->getName() : "nobody") << " ---\n";
    std::cout << "  Primary  : " << (primary ? primary->getName() : "empty")
              << (primaryActive ? "  [active]" : "") << "\n";
    std::cout << "  Secondary: " << (secondary ? secondary->getName() : "empty")
              << (!primaryActive ? "  [active]" : "") << "\n";
}
