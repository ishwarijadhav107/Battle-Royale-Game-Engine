#include "../../include/player/Player.h"
#include <algorithm>
#include <iostream>

// Auto-increment ID counter for constructors without explicit ID
static int s_nextPlayerId = 1000;

Player::Player(int id, const std::string& name, int health, int shield,
               const Position& position, int baseDamage)
    : id(id),
      name(name),
      health(std::max(0, health)),
      maxHealth(health > 0 ? health : 100),
      shield(std::max(0, shield)),
      maxShield(100),
      position(position),
      alive(health > 0),
      baseDamage(baseDamage > 0 ? baseDamage : 10),
      inventory(nullptr) {}

Player::Player(const std::string& name, int health, int shield,
               const Position& position, int baseDamage)
    : Player(++s_nextPlayerId, name, health, shield, position, baseDamage) {}

Player::~Player() {
    // Virtual destructor guarantees derived class cleanup.
    // Note: inventory lifetime is managed by Member 3 / owner.
}

void Player::takeDamage(int amount) {
    if (!alive || amount <= 0) {
        return;
    }

    // Shield absorbs damage first
    if (shield > 0) {
        if (shield >= amount) {
            shield -= amount;
            amount = 0;
        } else {
            amount -= shield;
            shield = 0;
        }
    }

    // Remaining damage penetrates to health
    if (amount > 0) {
        health -= amount;
        if (health <= 0) {
            health = 0;
            alive = false;
        }
    }
}

void Player::heal(int amount) {
    if (!alive || amount <= 0) {
        return;
    }

    health += amount;
    if (health > maxHealth) {
        health = maxHealth;
    }
}

void Player::rechargeShield(int amount) {
    if (!alive || amount <= 0) {
        return;
    }

    shield += amount;
    if (shield > maxShield) {
        shield = maxShield;
    }
}

int Player::getId() const {
    return id;
}

void Player::setId(int newId) {
    id = newId;
}

const std::string& Player::getName() const {
    return name;
}

void Player::setName(const std::string& newName) {
    name = newName;
}

int Player::getHealth() const {
    return health;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

void Player::setHealth(int newHealth) {
    health = std::max(0, std::min(newHealth, maxHealth));
    if (health == 0) {
        alive = false;
    }
}

int Player::getShield() const {
    return shield;
}

int Player::getMaxShield() const {
    return maxShield;
}

void Player::setShield(int newShield) {
    shield = std::max(0, std::min(newShield, maxShield));
}

Position Player::getPosition() const {
    return position;
}

void Player::setPosition(const Position& newPos) {
    position = newPos;
}

void Player::setPosition(float x, float y, float z) {
    position = Position(x, y, z);
}

bool Player::isAlive() const {
    return alive;
}

void Player::setAlive(bool status) {
    alive = status;
    if (!alive) {
        health = 0;
    }
}

int Player::getBaseDamage() const {
    return baseDamage;
}

void Player::setBaseDamage(int damage) {
    baseDamage = damage > 0 ? damage : 0;
}

Inventory* Player::getInventory() const {
    return inventory;
}

void Player::setInventory(Inventory* inv) {
    inventory = inv;
}

void Player::displayStatus() const {
    std::cout << "[" << getPlayerType() << "] ID: " << id
              << " | Name: " << name
              << " | HP: " << health << "/" << maxHealth
              << " | Shield: " << shield << "/" << maxShield
              << " | Pos: " << position
              << " | Status: " << (alive ? "ALIVE" : "ELIMINATED")
              << std::endl;
}
