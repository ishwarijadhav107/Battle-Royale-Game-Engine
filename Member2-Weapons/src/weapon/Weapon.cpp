#include "weapon/Weapon.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

int Weapon::shotsFired = 0;
int Weapon::totalDamageDealt = 0;
bool Weapon::verbose = true;

Weapon::Weapon(const std::string& name, int damage, float range, int maxAmmo)
    : name(name),
      damage(damage > 0 ? damage : 1),
      range(range > 0.0f ? range : 1.0f),
      ammo(maxAmmo > 0 ? maxAmmo : 0),
      maxAmmo(maxAmmo > 0 ? maxAmmo : 0) {}

void Weapon::log(const std::string& message) const {
    if (verbose) {
        std::cout << "[" << getWeaponType() << ": " << name << "] " << message << "\n";
    }
}

AttackResult Weapon::attack(const Player& attacker, Player& target) {
    AttackResult result;
    result.distance = attacker.getPosition().distanceTo(target.getPosition());

    // 1. Check that the attack is possible
    if (!attacker.isAlive()) {
        result.message = attacker.getName() + " is eliminated and cannot attack.";
    } else if (&attacker == &target) {
        result.message = attacker.getName() + " cannot attack themselves.";
    } else if (!target.isAlive()) {
        result.message = target.getName() + " is already eliminated.";
    } else if (result.distance > range) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << target.getName()
            << " is out of range (distance " << result.distance << ", range " << range << ").";
        result.message = oss.str();
    } else if (usesAmmo() && ammo == 0) {
        result.message = name + " is out of ammo - reload needed.";
    }
    if (!result.message.empty()) {
        log(result.message);
        return result;
    }

    // 2. Do the attack. The damage depends on the real weapon type (polymorphism).
    int dealt = calculateDamage(result.distance);
    if (usesAmmo()) {
        --ammo;
    }
    target.takeDamage(dealt);
    ++shotsFired;
    totalDamageDealt += dealt;

    result.success = true;
    result.damageDealt = dealt;
    result.targetEliminated = !target.isAlive();

    std::ostringstream oss;
    oss << attacker.getName() << " hits " << target.getName() << " with " << name
        << " for " << dealt << " damage.";
    if (result.targetEliminated) {
        oss << " [Match Event] " << target.getName() << " was eliminated by "
            << attacker.getName() << "!";
    }
    result.message = oss.str();
    log(result.message);
    return result;
}

bool Weapon::reload() {
    if (!usesAmmo()) {
        log("does not use ammunition.");
        return false;
    }
    if (ammo == maxAmmo) {
        log("magazine is already full.");
        return false;
    }
    ammo = maxAmmo;
    log("reloaded (" + std::to_string(ammo) + "/" + std::to_string(maxAmmo) + ").");
    return true;
}

void Weapon::displayInfo() const {
    std::cout << "=== " << getWeaponType() << ": " << name << " ===\n"
              << "  Damage: " << damage << "\n"
              << "  Range : " << range << "\n";
    if (usesAmmo()) {
        std::cout << "  Ammo  : " << ammo << "/" << maxAmmo << "\n";
    } else {
        std::cout << "  Ammo  : none\n";
    }
}

bool Weapon::usesAmmo() const { return maxAmmo > 0; }
bool Weapon::isEmpty() const { return usesAmmo() && ammo == 0; }

int Weapon::addAmmo(int rounds) {
    if (!usesAmmo() || rounds <= 0) {
        return 0;
    }
    int added = std::min(rounds, maxAmmo - ammo);
    ammo += added;
    return added;
}

const std::string& Weapon::getName() const { return name; }
int Weapon::getDamage() const { return damage; }
float Weapon::getRange() const { return range; }
int Weapon::getAmmo() const { return ammo; }
int Weapon::getMaxAmmo() const { return maxAmmo; }

int Weapon::getShotsFired() { return shotsFired; }
int Weapon::getTotalDamageDealt() { return totalDamageDealt; }
void Weapon::resetStats() { shotsFired = 0; totalDamageDealt = 0; }
void Weapon::setVerbose(bool enabled) { verbose = enabled; }
