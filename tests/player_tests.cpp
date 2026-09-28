#include <cassert>
#include <cmath>
#include <iostream>

#include "../include/player/AssaultPlayer.h"
#include "../include/player/MedicPlayer.h"
#include "../include/player/SniperPlayer.h"

int main() {
    // Player creation
    AssaultPlayer assault(1, "Assault");
    SniperPlayer sniper(2, "Sniper");
    MedicPlayer medic(3, "Medic");

    assert(assault.getId() == 1 && assault.getName() == "Assault");
    assert(sniper.isAlive() && medic.isAlive());

    // Damage is absorbed by shield before health.
    assault.takeDamage(70);
    assert(assault.getShield() == 0);
    assert(assault.getHealth() == 80);

    // Healing restores health, while lethal damage eliminates a player.
    MedicPlayer patient(4, "Patient", 100, 0);
    patient.takeDamage(40);
    patient.heal(20);
    assert(patient.getHealth() == 80);

    sniper.takeDamage(150);
    assert(sniper.getHealth() == 0);
    assert(!sniper.isAlive());

    // Abilities called through Player pointers demonstrate runtime polymorphism.
    AssaultPlayer abilityAssault(5, "Rager", 100, 0, Position(), 10);
    SniperPlayer abilitySniper(6, "Sharpshooter", 90, 0, Position(), 2.0);
    MedicPlayer abilityMedic(7, "Healer", 100, 0, Position(), 30);
    abilityMedic.takeDamage(50);

    Player* players[] = {&abilityAssault, &abilitySniper, &abilityMedic};
    for (Player* player : players) {
        player->useAbility();
    }

    assert(abilityAssault.getRageBonus() == 20);
    assert(std::abs(abilitySniper.getCritMultiplier() - 2.5) < 0.001);
    assert(abilityMedic.getHealth() == 80);

    std::cout << "All Player tests passed.\n";
    return 0;
}