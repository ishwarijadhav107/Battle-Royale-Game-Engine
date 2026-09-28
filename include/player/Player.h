#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "Position.h"

// Forward declaration for Member 3's Inventory module.
// Avoids implementing or coupling with Member 3's system prematurely.
class Inventory;

/**
 * @brief Abstract Base Class for all player archetypes in the Battle Royale Game Engine.
 * 
 * Demonstrates:
 * - Abstraction: defines high-level contract without concrete implementation details.
 * - Encapsulation: hides internal attributes behind protected access and public interfaces.
 * - Polymorphism: declares virtual destructor and pure virtual methods for derived classes.
 */
class Player {
protected:
    int id;
    std::string name;
    int health;
    int maxHealth;
    int shield;
    int maxShield;
    Position position;
    bool alive;
    int baseDamage;
    Inventory* inventory; // Aggregation with Member 3's module

public:
    // Constructors
    Player(int id, const std::string& name, int health = 100, int shield = 50,
           const Position& position = Position(), int baseDamage = 20);
    Player(const std::string& name, int health = 100, int shield = 50,
           const Position& position = Position(), int baseDamage = 20);

    // Virtual Destructor ensures safe polymorphic cleanup
    virtual ~Player();

    // Core Combat & Health Interface
    virtual void takeDamage(int amount);
    virtual void heal(int amount);
    virtual void rechargeShield(int amount);

    // Pure virtual functions (must be implemented by derived player classes)
    virtual void attack(Player* target) = 0;
    virtual void useAbility() = 0;
    virtual std::string getPlayerType() const = 0;

    // Getters & Setters (Encapsulation)
    int getId() const;
    void setId(int newId);

    const std::string& getName() const;
    void setName(const std::string& newName);

    int getHealth() const;
    int getMaxHealth() const;
    void setHealth(int newHealth);

    int getShield() const;
    int getMaxShield() const;
    void setShield(int newShield);

    Position getPosition() const;
    void setPosition(const Position& newPos);
    void setPosition(float x, float y, float z = 0.0f);

    bool isAlive() const;
    void setAlive(bool status);

    int getBaseDamage() const;
    void setBaseDamage(int damage);

    Inventory* getInventory() const;
    void setInventory(Inventory* inv);

    // Diagnostics / Information
    virtual void displayStatus() const;
};

#endif // PLAYER_H
