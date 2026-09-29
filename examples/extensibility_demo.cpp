// EXTENSIBILITY DEMO (faculty "change request" scenario)
//
// Goal: add a brand-new weapon (a Crossbow) WITHOUT touching any existing file in
// include/ or src/. Everything below lives in this single demo file.
//
// The engine (Weapon, Loadout, Player) works with the Crossbow immediately because
// it only depends on the Weapon interface.

#include <iostream>
#include <memory>

#include "player/AssaultPlayer.h"
#include "player/MedicPlayer.h"
#include "weapon/Loadout.h"
#include "weapon/MeleeWeapon.h"
#include "weapon/Weapon.h"

// ---- NEW WEAPON: ~15 lines -------------------------------------------------
class Crossbow : public Weapon {
public:
    Crossbow() : Weapon("Hunter Crossbow", 45, 70.0f, 1) {} // one bolt per reload
    int calculateDamage(float /*distance*/) const override { return baseDamage; } // no falloff
    std::string getWeaponType() const override { return "Crossbow"; }
    std::unique_ptr<Weapon> clone() const override { return std::make_unique<Crossbow>(*this); }
    float getReloadTime() const override { return 2.5f; }
    std::string getAttackVerb() const override { return "silently pins"; }
};
// -----------------------------------------------------------------------------

int main() {
    AssaultPlayer hunter(1, "Hunter", 100, 0, Position(0, 0, 0));
    MedicPlayer prey(2, "Prey", 100, 0, Position(40, 0, 0));

    Loadout loadout(&hunter);
    loadout.equipPrimary(std::make_unique<Crossbow>());
    loadout.equipSecondary(std::make_unique<MeleeWeapon>("Hatchet", 30, 2.0f));

    loadout.displayLoadout();
    loadout.attack(&prey);   // works: Loadout/Weapon/Player code was not modified
    loadout.attack(&prey);   // out of ammo (single-shot)
    loadout.reload();
    loadout.attack(&prey);

    std::cout << "\nPrey HP: " << prey.getHealth() << "\n"
              << "New weapon type added with zero changes to the engine.\n";
    return 0;
}
