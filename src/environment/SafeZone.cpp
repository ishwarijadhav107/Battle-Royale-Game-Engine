#include "environment/SafeZone.h"
#include <algorithm>
#include <cmath>
#include <iostream>

SafeZone::SafeZone(const Position& center, float radius, float shrinkRate,
                   float minimumRadius, int outsideDamage)
    : center(center), radius(std::max(0.0f, radius)),
      minimumRadius(std::max(0.0f, std::min(minimumRadius, radius))),
      shrinkRate(std::max(0.0f, shrinkRate)), outsideDamage(std::max(0, outsideDamage)) {}

float SafeZone::distanceFromCenter(const Position& p) const {
    float dx = p.x - center.x, dy = p.y - center.y;
    return std::sqrt(dx * dx + dy * dy);
}
bool SafeZone::contains(const Position& p) const { return distanceFromCenter(p) <= radius; }
bool SafeZone::contains(const Player& player) const { return contains(player.getPosition()); }

void SafeZone::shrink(float amount) {
    float reduction = amount < 0.0f ? shrinkRate : amount;
    if (reduction <= 0.0f) return;
    float oldRadius = radius;
    radius = std::max(minimumRadius, radius - reduction);
    std::cout << "[Safe Zone] Radius changed from " << oldRadius << " to " << radius << ".\n";
}

int SafeZone::applyOutsideDamage(Player& player) const {
    if (!player.isAlive() || contains(player)) return 0;
    player.takeDamage(outsideDamage);
    std::cout << "[Safe Zone] " << player.getName() << " is outside and takes "
              << outsideDamage << " damage.\n";
    return outsideDamage;
}
int SafeZone::applyOutsideDamage(const std::vector<Player*>& players) const {
    int affected = 0;
    for (Player* player : players) {
        if (player && player->isAlive() && !contains(*player)) {
            applyOutsideDamage(*player);
            ++affected;
        }
    }
    return affected;
}
Position SafeZone::getCenter() const { return center; }
float SafeZone::getRadius() const { return radius; }
float SafeZone::getShrinkRate() const { return shrinkRate; }
int SafeZone::getOutsideDamage() const { return outsideDamage; }
void SafeZone::setCenter(const Position& p) { center = p; }
void SafeZone::setShrinkRate(float rate) { shrinkRate = std::max(0.0f, rate); }
void SafeZone::setOutsideDamage(int damage) { outsideDamage = std::max(0, damage); }
void SafeZone::displayInfo() const {
    std::cout << "=== Safe Zone ===\nCenter: " << center << "\nRadius: " << radius
              << "\nShrink rate: " << shrinkRate << "\nOutside damage: " << outsideDamage << "\n";
}
