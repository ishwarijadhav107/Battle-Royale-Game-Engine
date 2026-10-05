// Demo of the Weapons module (Member 2) for the presentation.
#include <iostream>
#include <memory>

#include "player/AssaultPlayer.h"
#include "player/MedicPlayer.h"
#include "player/SniperPlayer.h"
#include "weapon/Gun.h"
#include "weapon/Loadout.h"
#include "weapon/MeleeWeapon.h"
#include "weapon/SniperRifle.h"

int main() {
    std::cout << "---- 1. The three weapon types ----\n";
    Gun rifle("AK-47", 22, 60.0f, 30);
    SniperRifle sniperRifle("Longshot", 60, 150.0f, 5, 0.0f);   // crit chance 0 = predictable demo
    MeleeWeapon axe("Fire Axe", 40, 2.5f);
    rifle.displayInfo();
    sniperRifle.displayInfo();
    axe.displayInfo();

    std::cout << "\n---- 2. Players with loadouts ----\n";
    AssaultPlayer rex(1, "Rex", 100, 50, Position(0, 0, 0));
    SniperPlayer vera(2, "Vera", 90, 40, Position(100, 0, 0));

    Loadout rexLoadout(&rex);
    rexLoadout.equipPrimary(std::make_unique<Gun>("AK-47", 22, 60.0f, 30));
    rexLoadout.equipSecondary(std::make_unique<MeleeWeapon>("Fire Axe", 40, 2.5f));

    Loadout veraLoadout(&vera);
    veraLoadout.equipPrimary(std::make_unique<SniperRifle>("Longshot", 60, 150.0f, 5, 0.0f));

    rexLoadout.displayLoadout();
    veraLoadout.displayLoadout();

    std::cout << "\n---- 3. Vera snipes Rex from 100 m ----\n";
    veraLoadout.attack(&rex);

    std::cout << "\n---- 4. Rex's rifle is out of range, so he moves closer ----\n";
    rexLoadout.attack(&vera);
    rex.setPosition(50, 0, 0);
    rexLoadout.attack(&vera);

    std::cout << "\n---- 5. Ammo and reload ----\n";
    Gun pistol("Pistol", 15, 30.0f, 2);
    AssaultPlayer shooter(3, "Shooter", 100, 0, Position(0, 0, 0));
    MedicPlayer dummy(4, "Dummy", 200, 0, Position(5, 0, 0));
    pistol.attack(shooter, dummy);
    pistol.attack(shooter, dummy);
    pistol.attack(shooter, dummy);   // out of ammo
    pistol.reload();
    pistol.attack(shooter, dummy);

    std::cout << "\n---- 6. Melee finish (switch to the axe) ----\n";
    vera.setHealth(10);
    vera.setShield(0);
    rex.setPosition(101, 0, 0);
    rexLoadout.switchWeapon();
    rexLoadout.attack(&vera);

    std::cout << "\n---- 7. Statistics (static members) ----\n"
              << "Shots fired       : " << Weapon::getShotsFired() << "\n"
              << "Total damage dealt: " << Weapon::getTotalDamageDealt() << "\n";
    return 0;
}
