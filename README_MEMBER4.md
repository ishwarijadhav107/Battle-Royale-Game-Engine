# Member 4 — Game Environment, Vehicles & Safe Zone

This module is written to match the uploaded team modules:
- Player classes in `include/player/` and `src/player/`
- `Player::getPosition()`, `Player::setPosition(...)`, `Player::isAlive()`, and `Player::takeDamage(...)`
- Existing `Position` type and C++17 / CMake conventions

## Files to copy into the shared repository

Copy the `include/environment/` and `src/environment/` folders into the repository root, along with `EnvironmentModule.cmake`. The `tests/` files are optional but recommended.

## Implemented features

- Abstract `Vehicle` base class and `Car`, `Truck`, `Motorcycle` derived classes.
- One player can enter a vehicle if alive and within 5 position units. A vehicle can hold one player at a time.
- A vehicle can move only while occupied and operational. Moving consumes fuel; vehicle types use different fuel rates.
- Entering/exiting, refueling, durability damage, and repairs.
- Circular safe zone in the x/y plane, with configurable center, radius, minimum radius, shrink rate, and outside-zone damage.
- Apply zone damage to one player or a list of players.
- `EnvironmentEventLog` records generic events such as `ZONE_CHANGE`, `ITEM_DISCOVERY`, and `PLAYER_ELIMINATION`.

## Build integration

The team repository currently has a `CMakeLists.txt` for PlayerLib. Member 2 and Member 3 supplied separate module CMake files. Once the team has combined the modules into the same repository root, add this line to the root `CMakeLists.txt` after `PlayerLib` is declared:

```cmake
include(EnvironmentModule.cmake)
```

Also ensure the Member 2 `WeaponModule.cmake` and Member 3 `InventoryModule.cmake` are included in the shared root CMake file in the order their README files specify. Do not replace the team's root `CMakeLists.txt` with this module file.

## Build and test

From the combined repository root:

```powershell
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Run the demo after building:

```powershell
.\build\environment_demo.exe
```

Depending on how your team's root CMake file defines targets and output paths, the executable may be under `build\Debug\environment_demo.exe` on a multi-configuration generator.

## Important integration note

This module is generated against the uploaded Member 1 API and does not require modifying `Player.h`. Vehicle occupancy stores a non-owning `Player*`; ensure a player object outlives the period in which the vehicle refers to it. The current simplified implementation updates the player's position when exiting the vehicle. A player inside a vehicle is tracked at the vehicle's position only after exit, so the match engine should treat vehicle position as the occupant's current location while driving.
