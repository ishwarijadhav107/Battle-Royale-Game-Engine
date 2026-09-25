# 🎮 Battle Royale Game Engine

> A modular and extensible **Battle Royale Game Engine** developed in **C++** to demonstrate core **Object-Oriented Programming (OOP)** concepts through a simplified multiplayer game simulation.

---

## 📌 About the Project

The **Battle Royale Game Engine** is a simplified multiplayer game simulation designed using Object-Oriented Programming principles.

The engine supports multiple player types, weapons, armor, vehicles, inventory systems, special abilities, health and shield mechanisms, shrinking safe zones, and match events.

The main focus of this project is to build a **modular and extensible system** where different game entities can have different behaviors using **runtime polymorphism** and other OOP concepts.

---

## 🎯 Objectives

- 🧑‍🤝‍🧑 Support multiple player archetypes with unique behaviors
- 🔫 Implement different weapons and attack mechanisms
- 🛡️ Implement health, shields, and armor systems
- 🎒 Manage player inventory and item acquisition
- 🚗 Support vehicles and different movement behaviors
- ⚡ Implement player-specific special abilities
- 🌐 Implement a shrinking safe zone
- ⚔️ Handle player encounters, attacks, damage, and eliminations
- 📊 Maintain game state and match statistics
- ➕ Allow new characters and weapons to be added without redesigning the core engine

---

## 🧠 OOP Concepts Demonstrated

| OOP Concept | Implementation |
|-------------|----------------|
| 🔹 Abstraction | Abstract classes for common game entities and behaviors |
| 🔹 Inheritance | Specialized player and weapon classes |
| 🔹 Runtime Polymorphism | Different attack, defense, movement, and ability behaviors |
| 🔹 Composition | Players composed with inventory, weapons, armor, etc. |
| 🔹 Association | Interaction between players, items, and game systems |
| 🔹 Dynamic Objects | Game entities created and managed at runtime |
| 🔹 Static Members | Shared match statistics and game information |

---

## 🧩 Main Game Components

### 🧑 Player System
A base `Player` abstraction is used to represent common player properties and behaviors. Different player types inherit from it and implement their own behaviors.

### 🔫 Weapon System
Weapons are modeled independently from players. Different weapons can have their own damage, attack range, and attack behavior.

### 🛡️ Health, Shield & Armor
Players have health and shield systems, while armor can reduce incoming damage.

### 🎒 Inventory System
Players can collect and manage weapons, armor, and other items through their inventory.

### 🚗 Vehicle System
Vehicles provide different movement options and can be associated with players during the match.

### ⚡ Ability System
Different player types can have unique special abilities implemented using runtime polymorphism.

### 🌐 Safe Zone
The safe zone gradually shrinks during the match. Players outside the safe zone receive damage.

### ⚔️ Match Events
The engine handles important events such as item collection, player encounters, attacks, zone changes, and player elimination.

---

## 🔄 Game Flow

```text
                 🎮 Start Match
                       │
                       ▼
             👥 Create Players
                       │
                       ▼
              🎒 Acquire Items
                       │
                       ▼
             ⚔️ Player Encounter
                       │
                       ▼
              🔫 Attack & Defense
                       │
                       ▼
             ❤️ Damage Calculation
                       │
                       ▼
              🌐 Safe Zone Shrinks
                       │
                       ▼
              💀 Player Elimination
                       │
                       ▼
             📊 Update Match Stats
                       │
                       ▼
                 🏆 Game End
