#include "../../include/player/SniperPlayer.h"
#include <iostream>
#include <cmath>
#include <iomanip>

SniperPlayer::SniperPlayer(int id, const std::string& name, int health, int shield,
                           const Position& position, double critMultiplier)
    : Player(id, name, health, shield, position, 30),
      critMultiplier(critMultiplier >= 1.0 ? critMultiplier : 1.0) {}

SniperPlayer::SniperPlayer(const std::string& name, int health, int shield,
                           const Position& position, double critMultiplier)
    : Player(name, health, shield, position, 30),
      critMultiplier(critMultiplier >= 1.0 ? critMultiplier : 1.0) {}

void SniperPlayer::attack(Player* target) {
    if (!alive) {
        std::cout << "[SniperPlayer " << name << "] Cannot attack: player is eliminated.\n";
        return;
    }
    if (target == nullptr) {
        std::cout << "[SniperPlayer " << name << "] Attack failed: target is null.\n";
        return;
    }
    if (!target->isAlive()) {
        std::cout << "[SniperPlayer " << name << "] Cannot attack: "
                  << target->getName() << " is already eliminated.\n";
        return;
    }

    int totalDamage = static_cast<int>(std::round(baseDamage * critMultiplier));
    std::cout << "[SniperPlayer " << name << "] executes Precision Shot on "
              << target->getName() << " dealing " << totalDamage
              << " damage (Base: " << baseDamage << " x " << critMultiplier << "x Crit)!\n";

    target->takeDamage(totalDamage);

    if (!target->isAlive()) {
        std::cout << "☠️ [Match Event] " << target->getName()
                  << " was sniped by " << name << "!\n";
    }
}

void SniperPlayer::useAbility() {
    if (!alive) {
        std::cout << "[SniperPlayer " << name << "] Cannot use ability: player is eliminated.\n";
        return;
    }

    double boost = 0.5;
    critMultiplier += boost;
    std::cout << "🎯 [SniperPlayer " << name
              << "] activates [Eagle Eye Focus]! Critical multiplier increased to "
              << critMultiplier << "x.\n";
}

std::string SniperPlayer::getPlayerType() const {
    return "SniperPlayer";
}

double SniperPlayer::getCritMultiplier() const {
    return critMultiplier;
}

void SniperPlayer::setCritMultiplier(double multiplier) {
    critMultiplier = multiplier >= 1.0 ? multiplier : 1.0;
}
