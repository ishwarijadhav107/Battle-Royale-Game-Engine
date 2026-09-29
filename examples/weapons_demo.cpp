// Live demonstration of the Weapons & Combat module (Member 2).
// Shows: polymorphic weapons, Loadout (composition/association), range, ammo, reload,
// elimination events and static match statistics.

#include <iostream>
#include <memory>
#include <vector>

#include "player/AssaultPlayer.h"
#include "player/MedicPlayer.h"
#include "player/SniperPlayer.h"
#include "weapon/Gun.h"
#include "weapon/Loadout.h"
#include "weapon/MeleeWeapon.h"
#include "weapon/Shotgun.h"
#include "weapon/SniperRifle.h"

static void section(const std::string& title) {
    std::cout << "\n########## " << title << " ##########\n";
}

int main() {
    // ------------------------------------------------------------------
    section("1. Polymorphic arsenal (one Weapon* interface, four behaviours)");
    std::vector<std::unique_ptr<Weapon>> arsenal;
    arsenal.push_back(std::make_unique<Gun>());
    arsenal.push_back(std::make_unique<Shotgun>());
    arsenal.push_back(std::make_unique<SniperRifle>());
    arsenal.push_back(std::make_unique<MeleeWeapon>());
    for (const auto& w : arsenal) {
        w->displayInfo();
    }

    // ------------------------------------------------------------------
    section("2. Players and their loadouts");
    AssaultPlayer rex(1, "Rex", 100, 50, Position(0, 0, 0));
    SniperPlayer vera(2, "Vera", 90, 40, Position(100, 0, 0));
    MedicPlayer doc(3, "Doc", 110, 60, Position(20, 0, 0));

    Loadout rexLoadout(&rex);
    rexLoadout.equipPrimary(std::make_unique<Gun>("AK-47", 22, 60.0f, 30, 2.0f));
    rexLoadout.equipSecondary(std::make_unique<MeleeWeapon>("Fire Axe", 40, 2.5f, "cleaves"));

    auto rifle = std::make_unique<SniperRifle>("Longshot", 60, 150.0f, 5, 3.5f, 0.0f);
    Loadout veraLoadout(&vera);
    veraLoadout.equipPrimary(std::move(rifle)); // crit chance 0 -> deterministic demo
    veraLoadout.equipSecondary(std::make_unique<Gun>("Pistol", 15, 30.0f, 12, 1.0f));

    Loadout docLoadout(&doc);
    docLoadout.equipPrimary(std::make_unique<Shotgun>());

    rexLoadout.displayLoadout();
    veraLoadout.displayLoadout();
    docLoadout.displayLoadout();

    // ------------------------------------------------------------------
    section("3. Encounter: Vera snipes Rex from 100 m");
    veraLoadout.attack(&rex);
    std::cout << "Rex now: HP " << rex.getHealth() << ", shield " << rex.getShield() << "\n";

    section("4. Rex's rifle cannot reach Vera (range 60) - he closes in and fires");
    rexLoadout.attack(&vera);       // out of range
    rex.setPosition(50, 0, 0);      // distance 50 -> inside falloff zone
    rexLoadout.attack(&vera);
    std::cout << "Vera now: HP " << vera.getHealth() << ", shield " << vera.getShield() << "\n";

    section("5. Doc blasts Rex with the shotgun at close vs far range");
    doc.setPosition(55, 0, 0);      // 5 m from Rex -> most pellets hit
    docLoadout.attack(&rex);
    doc.setPosition(64, 0, 0);      // 14 m from Rex -> almost all pellets miss
    docLoadout.attack(&rex);

    section("6. Ammo and reload");
    Gun pistol("Pistol", 15, 30.0f, 2, 1.0f);
    AssaultPlayer dummyShooter(4, "Dummy", 100, 0, Position(0, 0, 0));
    MedicPlayer dummyTarget(5, "Target", 200, 0, Position(5, 0, 0));
    pistol.attack(dummyShooter, dummyTarget);
    pistol.attack(dummyShooter, dummyTarget);
    pistol.attack(dummyShooter, dummyTarget); // empty
    pistol.reload();
    pistol.attack(dummyShooter, dummyTarget);

    section("7. Melee finish: Rex switches to the axe and eliminates a weakened Vera");
    vera.setHealth(30);
    vera.setShield(0);
    rex.setPosition(101, 0, 0);
    rexLoadout.switchWeapon();
    rexLoadout.attack(&vera);
    std::cout << "Vera alive? " << (vera.isAlive() ? "yes" : "no") << "\n";

    // ------------------------------------------------------------------
    section("8. Match statistics from static members");
    std::cout << "Weapons created     : " << Weapon::getWeaponsCreated() << "\n"
              << "Weapons alive       : " << Weapon::getWeaponsAlive() << "\n"
              << "Total shots fired   : " << Weapon::getTotalShotsFired() << "\n"
              << "Total damage dealt  : " << Weapon::getTotalDamageDealt() << "\n";
    return 0;
}
