#ifndef SAFE_ZONE_H
#define SAFE_ZONE_H

#include <vector>
#include "player/Player.h"

/**
 * Circular safe zone in the game's x/y plane.
 * Z is ignored when checking whether a player is inside the zone.
 */
class SafeZone {
private:
    Position center;
    float radius;
    float minimumRadius;
    float shrinkRate;
    int outsideDamage;

public:
    SafeZone(const Position& center = Position(), float radius = 500.0f,
             float shrinkRate = 5.0f, float minimumRadius = 20.0f,
             int outsideDamage = 10);

    bool contains(const Position& position) const;
    bool contains(const Player& player) const;
    float distanceFromCenter(const Position& position) const;
    void shrink(float amount = -1.0f);
    int applyOutsideDamage(Player& player) const;
    int applyOutsideDamage(const std::vector<Player*>& players) const;

    Position getCenter() const;
    float getRadius() const;
    float getShrinkRate() const;
    int getOutsideDamage() const;
    void setCenter(const Position& newCenter);
    void setShrinkRate(float rate);
    void setOutsideDamage(int damage);
    void displayInfo() const;
};
#endif
