#ifndef ASSAULT_PLAYER_H
#define ASSAULT_PLAYER_H

#include "Player.h"

/**
 * @brief Assault archetype focusing on aggressive close/mid-range combat.
 * Uses rageBonus to amplify attack damage and special ability to surge rage.
 */
class AssaultPlayer : public Player {
private:
    int rageBonus;

public:
    // Constructors
    AssaultPlayer(int id, const std::string& name, int health = 100, int shield = 50,
                  const Position& position = Position(), int rageBonus = 15);
    AssaultPlayer(const std::string& name = "AssaultSoldier", int health = 100, int shield = 50,
                  const Position& position = Position(), int rageBonus = 15);

    virtual ~AssaultPlayer() override = default;

    // Polymorphic Overrides
    void attack(Player* target) override;
    void useAbility() override;
    std::string getPlayerType() const override;

    // Archetype-specific Getters/Setters
    int getRageBonus() const;
    void setRageBonus(int bonus);
};

#endif // ASSAULT_PLAYER_H
