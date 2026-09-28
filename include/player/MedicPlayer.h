#ifndef MEDIC_PLAYER_H
#define MEDIC_PLAYER_H

#include "Player.h"

/**
 * @brief Medic archetype specializing in sustain, resilience, and healing abilities.
 * Uses healPower to restore health and special ability to activate medical regeneration.
 */
class MedicPlayer : public Player {
private:
    int healPower;

public:
    // Constructors
    MedicPlayer(int id, const std::string& name, int health = 110, int shield = 60,
                const Position& position = Position(), int healPower = 25);
    MedicPlayer(const std::string& name = "CombatMedic", int health = 110, int shield = 60,
                const Position& position = Position(), int healPower = 25);

    virtual ~MedicPlayer() override = default;

    // Polymorphic Overrides
    void attack(Player* target) override;
    void useAbility() override;
    std::string getPlayerType() const override;

    // Ally Healing Support
    void healTarget(Player* ally);

    // Archetype-specific Getters/Setters
    int getHealPower() const;
    void setHealPower(int power);
};

#endif // MEDIC_PLAYER_H
