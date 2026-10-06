#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "item/ArmorItem.h"
#include "item/HealthPotion.h"
#include "item/Inventory.h"
#include "item/Item.h"
#include "item/PowerUp.h"
#include "item/WeaponItem.h"
#include "player/AssaultPlayer.h"
#include "weapon/Gun.h"

static int checks = 0, failures = 0;

#define CHECK(cond)                                                      \
    do {                                                                 \
        ++checks;                                                        \
        if (!(cond)) {                                                   \
            ++failures;                                                  \
            std::cerr << "FAILED: " #cond " (line " << __LINE__ << ")\n"; \
        }                                                                \
    } while (0)

#define CHECK_CONTAINS(text, part) CHECK((text).find(part) != std::string::npos)

// Captures everything printed to std::cout while it is alive (keeps test output clean).
struct CaptureCout {
    std::ostringstream buffer;
    std::streambuf* old;
    CaptureCout() : old(std::cout.rdbuf(buffer.rdbuf())) {}
    ~CaptureCout() { std::cout.rdbuf(old); }
    std::string str() const { return buffer.str(); }
};

static AssaultPlayer makePlayer() {
    return AssaultPlayer(1, "Tester", 100, 0, Position(0, 0, 0));
}

// Test-only item used to check ownership and polymorphic calls.
static int trackedDestroyed = 0;
static int trackedUses = 0;
class TrackedItem : public Item {
public:
    TrackedItem() : Item("Tracked", ItemType::PowerUp, 1) {}
    ~TrackedItem() override { ++trackedDestroyed; }
    void use(Player&) override { ++trackedUses; }
};

static void testItemBasics() {
    ArmorItem armor("Vest", 25);
    CHECK(armor.getName() == "Vest");
    CHECK(armor.getType() == ItemType::Armor);
    CHECK(armor.getValue() == 25);
    CHECK(armor.getArmorValue() == 25);

    HealthPotion potion("Medkit", 30);
    CHECK(potion.getType() == ItemType::HealthPotion);
    CHECK(potion.getHealAmount() == 30);

    PowerUp boost("Speed Boost", 10);
    CHECK(boost.getName() == "Speed Boost");
    CHECK(boost.getType() == ItemType::PowerUp);
    CHECK(boost.getPowerValue() == 10);
}

static void testHealthPotion() {
    AssaultPlayer p = makePlayer();
    p.takeDamage(50);
    int before = p.getHealth();
    CHECK(before < p.getMaxHealth());

    HealthPotion small("Bandage", 10);
    {
        CaptureCout quiet;
        small.use(p);
    }
    CHECK(p.getHealth() == std::min(before + 10, p.getMaxHealth()));

    HealthPotion huge("Mega Kit", 1000);
    {
        CaptureCout quiet;
        huge.use(p);
    }
    CHECK(p.getHealth() == p.getMaxHealth());      // never above max health

    p.takeDamage(20);
    int hurt = p.getHealth();
    HealthPotion invalid("Broken", -5);
    {
        CaptureCout quiet;
        invalid.use(p);
    }
    CHECK(p.getHealth() == hurt);                  // invalid potion changes nothing
}

static void testArmor() {
    AssaultPlayer p = makePlayer();
    int before = p.getShield();

    ArmorItem vest("Vest", 25);
    {
        CaptureCout quiet;
        vest.use(p);
    }
    CHECK(p.getShield() == std::min(before + 25, p.getMaxShield()));

    ArmorItem heavy("Heavy Armor", 1000);
    {
        CaptureCout quiet;
        heavy.use(p);
    }
    CHECK(p.getShield() == p.getMaxShield());      // never above max shield

    int full = p.getShield();
    ArmorItem invalid("Broken", 0);
    {
        CaptureCout quiet;
        invalid.use(p);
    }
    CHECK(p.getShield() == full);
}

static void testWeaponItem() {
    Gun gun("Rifle", 20, 60.0f, 30);
    WeaponItem item("Rifle", &gun);
    AssaultPlayer p = makePlayer();

    CHECK(item.getType() == ItemType::Weapon);
    CHECK(item.getWeapon() == &gun);

    std::string info;
    {
        CaptureCout cap;
        item.use(p);
        item.displayInfo();
        info = cap.str();
    }
    CHECK_CONTAINS(info, "Tester selected weapon: Rifle");
    CHECK_CONTAINS(info, "Damage: 20");
    CHECK_CONTAINS(info, "Ammo: 30/30");

    WeaponItem empty("Empty", nullptr);
    CHECK(empty.getWeapon() == nullptr);
    std::string emptyInfo;
    {
        CaptureCout cap;
        empty.use(p);
        empty.displayInfo();
        emptyInfo = cap.str();
    }
    CHECK_CONTAINS(emptyInfo, "cannot use Empty");
    CHECK_CONTAINS(emptyInfo, "No weapon assigned.");
}

static void testInventoryAddGetRemove() {
    Inventory inv;
    CHECK(inv.getItemCount() == 0);

    Item* potion = new HealthPotion("Medkit", 30);
    Item* armor = new ArmorItem("Vest", 25);
    inv.addItem(potion);
    inv.addItem(armor);
    inv.addItem(nullptr);                          // ignored
    CHECK(inv.getItemCount() == 2);

    CHECK(inv.getItem(0) == potion);
    CHECK(inv.getItem(1) == armor);
    CHECK(inv.getItem(-1) == nullptr);
    CHECK(inv.getItem(2) == nullptr);

    CHECK(inv.removeItem(potion));
    CHECK(inv.getItemCount() == 1);
    CHECK(inv.getItem(0) == armor);
    CHECK(!inv.removeItem(potion));                // already removed
    CHECK(!inv.removeItem(nullptr));
    delete potion;                                 // removeItem does not delete
}

static void testInventoryUseAndDisplay() {
    Inventory inv;
    {
        CaptureCout cap;
        inv.displayInventory();
        CHECK_CONTAINS(cap.str(), "Inventory is empty.");
    }

    inv.addItem(new HealthPotion("Medkit", 30));
    inv.addItem(new ArmorItem("Vest", 25));

    {
        CaptureCout cap;
        inv.displayInventory();
        std::string text = cap.str();
        CHECK_CONTAINS(text, "Medkit");
        CHECK_CONTAINS(text, "Heal Amount: 30");
        CHECK_CONTAINS(text, "Vest");
        CHECK_CONTAINS(text, "Armor Value: 25");
    }

    AssaultPlayer p = makePlayer();
    p.takeDamage(50);
    int before = p.getHealth();
    {
        CaptureCout quiet;
        inv.useItem(0, p);
    }
    CHECK(p.getHealth() == std::min(before + 30, p.getMaxHealth()));

    {
        CaptureCout cap;
        inv.useItem(99, p);
        inv.useItem(-1, p);
        CHECK_CONTAINS(cap.str(), "Invalid inventory item.");
    }
    CHECK(inv.getItemCount() == 2);                // using an item does not remove it
}

static void testInventoryOwnership() {
    trackedDestroyed = 0;
    {
        Inventory inv;
        inv.addItem(new TrackedItem());
        inv.addItem(new TrackedItem());
    }
    CHECK(trackedDestroyed == 2);                  // Inventory deletes its items

    trackedDestroyed = 0;
    {
        Inventory inv;
        Item* removed = new TrackedItem();
        inv.addItem(removed);
        inv.addItem(new TrackedItem());
        CHECK(inv.removeItem(removed));
        CHECK(trackedDestroyed == 0);              // removed item is handed back, not deleted
        delete removed;
        CHECK(trackedDestroyed == 1);
    }
    CHECK(trackedDestroyed == 2);
}

static void testPolymorphism() {
    Gun gun("Rifle", 20, 60.0f, 30);

    std::vector<std::unique_ptr<Item>> items;
    items.push_back(std::make_unique<ArmorItem>("Vest", 25));
    items.push_back(std::make_unique<HealthPotion>("Medkit", 30));
    items.push_back(std::make_unique<WeaponItem>("Rifle", &gun));
    items.push_back(std::make_unique<PowerUp>("Speed Boost", 10));

    const ItemType types[] = {ItemType::Armor, ItemType::HealthPotion,
                              ItemType::Weapon, ItemType::PowerUp};
    for (size_t i = 0; i < items.size(); ++i) {
        CHECK(items[i]->getType() == types[i]);    // same call, different item
    }

    AssaultPlayer p = makePlayer();
    p.takeDamage(50);
    int hp = p.getHealth();
    {
        CaptureCout quiet;
        items[0]->use(p);                          // use() on base pointer -> ArmorItem
        items[1]->use(p);                          // use() on base pointer -> HealthPotion
    }
    CHECK(p.getShield() == std::min(25, p.getMaxShield()));
    CHECK(p.getHealth() == std::min(hp + 30, p.getMaxHealth()));

    trackedUses = 0;
    Inventory inv;
    inv.addItem(new TrackedItem());
    {
        CaptureCout quiet;
        inv.useItem(0, p);
    }
    CHECK(trackedUses == 1);                       // Inventory calls the item's own use()
}

int main() {
    testItemBasics();
    testHealthPotion();
    testArmor();
    testWeaponItem();
    testInventoryAddGetRemove();
    testInventoryUseAndDisplay();
    testInventoryOwnership();
    testPolymorphism();

    std::cout << "Inventory tests: " << (checks - failures) << "/" << checks << " checks passed.\n";
    return failures == 0 ? 0 : 1;
}
