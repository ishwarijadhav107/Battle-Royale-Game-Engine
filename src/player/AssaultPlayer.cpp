#include "../../include/player/AssaultPlayer.h"
#include <iostream>

AssaultPlayer::AssaultPlayer(int id, const std::string& name, int health, int shield,
                             const Position& position, int rageBonus)
    : Player(id, name, health, shield, position, 25),
      rageBonus(rageBonus > 0 ? rageBonus : 0) {}

AssaultPlayer::AssaultPlayer(const std::string& name, int health, int shield,
                             const Position& position, int rageBonus)
    : Player(name, health, shield, position, 25),
      rageBonus(rageBonus > 0 ? rageBonus : 0) {}

void AssaultPlayer::attack(Player* target) {
    if (!alive) {
        std::cout << "[AssaultPlayer " << name << "] Cannot attack: player is eliminated.\n";
        return;
    }
    if (target == nullptr) {
        std::cout << "[AssaultPlayer " << name << "] Attack failed: target is null.\n";
        return;
    }
    if (!target->isAlive()) {
        std::cout << "[AssaultPlayer " << name << "] Cannot attack: "
                  << target->getName() << " is already eliminated.\n";
        return;
    }

    int totalDamage = baseDamage + rageBonus;
    std::cout << "[AssaultPlayer " << name << "] executes Rage Strike on "
              << target->getName() << " dealing " << totalDamage
              << " damage (Base: " << baseDamage << " + Rage: " << rageBonus << ")!\n";

    target->takeDamage(totalDamage);

    if (!target->isAlive()) {
        std::cout << "☠️ [Match Event] " << target->getName()
                  << " was eliminated by " << name << "!\n";
    }
}

void AssaultPlayer::useAbility() {
    if (!alive) {
        std::cout << "[AssaultPlayer " << name << "] Cannot use ability: player is eliminated.\n";
        return;
    }

    int boost = 10;
    rageBonus += boost;
    std::cout << "🔥 [AssaultPlayer " << name
              << "] activates [Berserker Surge]! Rage bonus increased by "
              << boost << " (Current Rage: " << rageBonus << ").\n";
}

std::string AssaultPlayer::getPlayerType() const {
    return "AssaultPlayer";
}

int AssaultPlayer::getRageBonus() const {
    return rageBonus;
}

void AssaultPlayer::setRageBonus(int bonus) {
    rageBonus = bonus > 0 ? bonus : 0;
}
