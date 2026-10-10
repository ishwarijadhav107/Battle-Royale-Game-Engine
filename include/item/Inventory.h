#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

class Item;
class Player;

   /**
    * @brief Manages items carried by a player.
    *
    * Demonstrates composition: the inventory owns its items and
    * deletes them in its destructor.
    */
class Inventory {
private:
    std::vector<Item*> items;

public:
    Inventory() = default;
    ~Inventory();

    void addItem(Item* item);
    bool removeItem(Item* item);
    Item* getItem(int index) const;

    int getItemCount() const;
    void displayInventory() const;
    void useItem(int index, Player& player);
};

#endif // INVENTORY_H
