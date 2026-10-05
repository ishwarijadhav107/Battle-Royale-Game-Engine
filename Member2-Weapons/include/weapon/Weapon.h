#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "player/Player.h"

// Result of one attack. Useful for the Game Engine (kills, statistics, messages).
struct AttackResult {
    bool success = false;           // true if the attack was actually carried out
    int damageDealt = 0;            // damage sent to the target
    float distance = 0.0f;          // distance between attacker and target
    bool targetEliminated = false;  // true if this attack eliminated the target
    std::string message;            // description of what happened
};

// Abstract base class for all weapons.
//   Abstraction : calculateDamage() and getWeaponType() are pure virtual
//   Encapsulation: data is protected, accessed through getters
//   Inheritance : Gun, SniperRifle and MeleeWeapon derive from Weapon
//   Polymorphism: attack() calls the virtual calculateDamage()
class Weapon {
protected:
    std::string name;
    int damage;
    float range;
    int ammo;
    int maxAmmo;   // 0 means the weapon does not use ammunition

    void log(const std::string& message) const;

private:
    // Static members: statistics shared by all weapons (used for match statistics)
    static int shotsFired;
    static int totalDamageDealt;
    static bool verbose;

public:
    Weapon(const std::string& name, int damage, float range, int maxAmmo);
    virtual ~Weapon() = default;

    // Checks range / ammo / alive status, then applies the weapon's own damage.
    AttackResult attack(const Player& attacker, Player& target);

    virtual bool reload();
    virtual int calculateDamage(float distance) const = 0;  // each weapon decides its damage
    virtual std::string getWeaponType() const = 0;
    virtual void displayInfo() const;

    bool usesAmmo() const;
    bool isEmpty() const;
    int addAmmo(int rounds);   // for ammo pickups; returns how many rounds were added

    const std::string& getName() const;
    int getDamage() const;
    float getRange() const;
    int getAmmo() const;
    int getMaxAmmo() const;

    static int getShotsFired();
    static int getTotalDamageDealt();
    static void resetStats();
    static void setVerbose(bool enabled);   // false = no console messages
};

#endif // WEAPON_H
