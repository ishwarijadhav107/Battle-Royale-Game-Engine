#ifndef SNIPER_PLAYER_H
#define SNIPER_PLAYER_H

#include "Player.h"

/**
 * @brief Sniper archetype specializing in long-range precision and critical strikes.
 * Uses critMultiplier to scale damage and special ability to enhance critical focus.
 */
class SniperPlayer : public Player {
private:
    double critMultiplier;

public:
    // Constructors
    SniperPlayer(int id, const std::string& name, int health = 90, int shield = 40,
                 const Position& position = Position(), double critMultiplier = 2.0);
    SniperPlayer(const std::string& name = "SniperScout", int health = 90, int shield = 40,
                 const Position& position = Position(), double critMultiplier = 2.0);

    virtual ~SniperPlayer() override = default;

    // Polymorphic Overrides
    void attack(Player* target) override;
    void useAbility() override;
    std::string getPlayerType() const override;

    // Archetype-specific Getters/Setters
    double getCritMultiplier() const;
    void setCritMultiplier(double multiplier);
};

#endif // SNIPER_PLAYER_H
