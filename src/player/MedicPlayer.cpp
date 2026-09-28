#include "../../include/player/MedicPlayer.h"
#include <iostream>

MedicPlayer::MedicPlayer(int id, const std::string& name, int health, int shield,
                         const Position& position, int healPower)
    : Player(id, name, health, shield, position, 18),
      healPower(healPower > 0 ? healPower : 10) {}

MedicPlayer::MedicPlayer(const std::string& name, int health, int shield,
                         const Position& position, int healPower)
    : Player(name, health, shield, position, 18),
      healPower(healPower > 0 ? healPower : 10) {}

void MedicPlayer::attack(Player* target) {
    if (!alive) {
        std::cout << "[MedicPlayer " << name << "] Cannot attack: player is eliminated.\n";
        return;
    }
    if (target == nullptr) {
        std::cout << "[MedicPlayer " << name << "] Attack failed: target is null.\n";
        return;
    }
    if (!target->isAlive()) {
        std::cout << "[MedicPlayer " << name << "] Cannot attack: "
                  << target->getName() << " is already eliminated.\n";
        return;
    }

    std::cout << "[MedicPlayer " << name << "] attacks "
              << target->getName() << " with Bio-Dart dealing "
              << baseDamage << " damage!\n";

    target->takeDamage(baseDamage);

    if (!target->isAlive()) {
        std::cout << "☠️ [Match Event] " << target->getName()
                  << " was eliminated by " << name << "!\n";
    }
}

void MedicPlayer::useAbility() {
    if (!alive) {
        std::cout << "[MedicPlayer " << name << "] Cannot use ability: player is eliminated.\n";
        return;
    }

    int oldHealth = health;
    heal(healPower);
    int restored = health - oldHealth;

    std::cout << "💖 [MedicPlayer " << name
              << "] activates [Medical Field]! Restored " << restored
              << " HP (Health: " << health << "/" << maxHealth << ").\n";
}

void MedicPlayer::healTarget(Player* ally) {
    if (!alive) {
        std::cout << "[MedicPlayer " << name << "] Cannot heal ally: medic is eliminated.\n";
        return;
    }
    if (ally == nullptr) {
        std::cout << "[MedicPlayer " << name << "] Heal failed: ally is null.\n";
        return;
    }
    if (!ally->isAlive()) {
        std::cout << "[MedicPlayer " << name << "] Cannot heal "
                  << ally->getName() << ": player is already eliminated.\n";
        return;
    }

    int oldHealth = ally->getHealth();
    ally->heal(healPower);
    int restored = ally->getHealth() - oldHealth;

    std::cout << "💉 [MedicPlayer " << name << "] treats ally "
              << ally->getName() << " restoring " << restored
              << " HP (Ally HP: " << ally->getHealth()
              << "/" << ally->getMaxHealth() << ").\n";
}

std::string MedicPlayer::getPlayerType() const {
    return "MedicPlayer";
}

int MedicPlayer::getHealPower() const {
    return healPower;
}

void MedicPlayer::setHealPower(int power) {
    healPower = power > 0 ? power : 0;
}
