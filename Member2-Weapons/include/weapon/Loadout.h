#ifndef LOADOUT_H
#define LOADOUT_H

#include <memory>

#include "weapon/Weapon.h"

// The weapons a player carries: one primary and one secondary slot.
//   Composition: the Loadout OWNS its weapons (unique_ptr) - they are destroyed with it.
//   Association: the Loadout only KNOWS its owner (Player*) and never deletes it.
class Loadout {
private:
    Player* owner;                      // association (not owned)
    std::unique_ptr<Weapon> primary;    // composition (owned)
    std::unique_ptr<Weapon> secondary;  // composition (owned)
    bool primaryActive;

public:
    explicit Loadout(Player* owner = nullptr);

    void equipPrimary(std::unique_ptr<Weapon> weapon);
    void equipSecondary(std::unique_ptr<Weapon> weapon);
    bool switchWeapon();                  // false if the other slot is empty
    Weapon* getActiveWeapon() const;      // nullptr if unarmed

    AttackResult attack(Player* target);  // attack with the active weapon
    bool reload();                        // reload the active weapon
    void displayLoadout() const;
};

#endif // LOADOUT_H
