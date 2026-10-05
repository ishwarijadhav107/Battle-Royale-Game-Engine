// Unit tests for the Weapons module (Member 2).
#include <iostream>
#include <memory>
#include <vector>

#include "player/AssaultPlayer.h"
#include "player/MedicPlayer.h"
#include "weapon/Gun.h"
#include "weapon/Loadout.h"
#include "weapon/MeleeWeapon.h"
#include "weapon/SniperRifle.h"

static int checks = 0, failures = 0;

#define CHECK(cond)                                                      \
    do {                                                                 \
        ++checks;                                                        \
        if (!(cond)) {                                                   \
            ++failures;                                                  \
            std::cerr << "FAILED: " #cond " (line " << __LINE__ << ")\n"; \
        }                                                                \
    } while (0)

// A shooter at the origin and a target at (distance, 0, 0).
static AssaultPlayer shooter() { return AssaultPlayer(1, "Shooter", 100, 0, Position(0, 0, 0)); }
static MedicPlayer target(float distance, int health = 100) {
    return MedicPlayer(2, "Target", health, 0, Position(distance, 0, 0));
}

static void testGun() {
    Gun gun("Rifle", 20, 60.0f, 30);
    CHECK(gun.getWeaponType() == "Gun");
    CHECK(gun.calculateDamage(10.0f) == 20);   // full damage up to half range
    CHECK(gun.calculateDamage(45.0f) == 15);   // falling off
    CHECK(gun.calculateDamage(60.0f) == 10);   // 50% at max range

    AssaultPlayer s = shooter();
    MedicPlayer t = target(10.0f);
    AttackResult r = gun.attack(s, t);
    CHECK(r.success && r.damageDealt == 20);
    CHECK(t.getHealth() == 80);
    CHECK(gun.getAmmo() == 29);
}

static void testRangeAndAmmo() {
    Gun gun("Pistol", 15, 30.0f, 2);
    AssaultPlayer s = shooter();
    MedicPlayer far = target(31.0f);
    MedicPlayer near = target(5.0f);

    CHECK(!gun.attack(s, far).success);        // out of range
    CHECK(gun.getAmmo() == 2);                 // no ammo wasted

    CHECK(gun.attack(s, near).success);
    CHECK(gun.attack(s, near).success);
    CHECK(gun.isEmpty());
    CHECK(!gun.attack(s, near).success);       // out of ammo
    CHECK(near.getHealth() == 70);

    CHECK(gun.reload());
    CHECK(gun.getAmmo() == 2);
    CHECK(!gun.reload());                      // already full

    gun.attack(s, near);
    CHECK(gun.addAmmo(10) == 1);               // only fills the magazine
}

static void testSniper() {
    SniperRifle sniper("Sniper", 60, 150.0f, 5, 0.0f, 1.5f, 20.0f);   // no crits
    CHECK(sniper.getWeaponType() == "Sniper");
    CHECK(sniper.calculateDamage(100.0f) == 60);
    CHECK(sniper.calculateDamage(5.0f) == 24);   // too close: 40%

    sniper.setCritChance(1.0f);                  // always crit
    CHECK(sniper.calculateDamage(100.0f) == 90); // 60 x 1.5
    sniper.setCritChance(5.0f);                  // clamped to 1.0
    CHECK(sniper.getCritChance() == 1.0f);
}

static void testMelee() {
    MeleeWeapon knife("Knife", 35, 2.0f);
    AssaultPlayer s = shooter();
    MedicPlayer far = target(5.0f);
    MedicPlayer near = target(1.0f);

    CHECK(!knife.usesAmmo());
    CHECK(!knife.reload());
    CHECK(!knife.attack(s, far).success);        // out of reach
    CHECK(knife.attack(s, near).damageDealt == 35);
    CHECK(near.getHealth() == 65);
}

static void testPolymorphism() {
    std::vector<std::unique_ptr<Weapon>> weapons;
    weapons.push_back(std::make_unique<Gun>());
    weapons.push_back(std::make_unique<SniperRifle>());
    weapons.push_back(std::make_unique<MeleeWeapon>());

    const char* types[] = {"Gun", "Sniper", "Melee"};
    for (size_t i = 0; i < weapons.size(); ++i) {
        CHECK(weapons[i]->getWeaponType() == types[i]);   // same call, different result
        AssaultPlayer s = shooter();
        MedicPlayer t = target(1.0f);
        CHECK(weapons[i]->attack(s, t).success);
    }
}

static void testEliminationAndInvalidAttacks() {
    Gun gun("Rifle", 20, 60.0f, 30);
    AssaultPlayer s = shooter();
    MedicPlayer weak = target(5.0f, 15);

    AttackResult r = gun.attack(s, weak);
    CHECK(r.success && r.targetEliminated);
    CHECK(!weak.isAlive());
    CHECK(!gun.attack(s, weak).success);         // target already dead
    CHECK(!gun.attack(s, s).success);            // cannot attack yourself

    AssaultPlayer dead = shooter();
    dead.takeDamage(1000);
    MedicPlayer alive = target(5.0f);
    CHECK(!gun.attack(dead, alive).success);     // dead players cannot attack
}

static void testStatistics() {
    Weapon::resetStats();
    Gun gun("Rifle", 20, 60.0f, 30);
    AssaultPlayer s = shooter();
    MedicPlayer t = target(5.0f);
    gun.attack(s, t);
    gun.attack(s, t);
    CHECK(Weapon::getShotsFired() == 2);
    CHECK(Weapon::getTotalDamageDealt() == 40);
}

static void testLoadout() {
    AssaultPlayer owner(10, "Owner", 100, 0, Position(0, 0, 0));
    MedicPlayer t = target(1.0f);
    Loadout loadout(&owner);

    CHECK(loadout.getActiveWeapon() == nullptr);
    CHECK(!loadout.attack(&t).success);          // unarmed
    CHECK(!loadout.switchWeapon());

    loadout.equipPrimary(std::make_unique<Gun>("Rifle", 20, 60.0f, 30));
    loadout.equipSecondary(std::make_unique<MeleeWeapon>("Knife", 35, 2.0f));
    CHECK(loadout.attack(&t).damageDealt == 20);
    CHECK(loadout.switchWeapon());
    CHECK(loadout.getActiveWeapon()->getName() == "Knife");
    CHECK(loadout.attack(&t).damageDealt == 35);
    CHECK(t.getHealth() == 45);
    CHECK(!loadout.attack(nullptr).success);
}

int main() {
    Weapon::setVerbose(false);   // keep test output clean
    testGun();
    testRangeAndAmmo();
    testSniper();
    testMelee();
    testPolymorphism();
    testEliminationAndInvalidAttacks();
    testStatistics();
    testLoadout();

    std::cout << "Weapon tests: " << (checks - failures) << "/" << checks << " checks passed.\n";
    return failures == 0 ? 0 : 1;
}
