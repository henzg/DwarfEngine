#pragma once
#include <unordered_map>
#include "Dwarf/include/DynamicArray.hpp"
#include <string>
/*Library of component definitions*/

namespace Aether {

    struct PositionComponent {
        float x, y;
    };

    struct HealthComponent {
        float hp, maxHp;
    };

    struct StatsComponent {
        float speed, carryWeight; // These should act as multipliers maybe?
    };

    struct VelocityComponent {
        float dx, dy;
    };

    struct ResourceComponent {
        std::string name; // probably should be a custom type that has the values of each element
                          // but string for now
        float amount;
    };

    struct InventoryComponent {
        float maxWeight, currWeight;
        std::unordered_map<std::string, float> items;
    };

    struct KnowledgeComponent {
        Dwarf::DynamicArray<std::string> discoveredElements;
        Dwarf::DynamicArray<std::string> unlockedRecipes;
    };

} // namespace Aether
