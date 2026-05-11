#pragma once
#include <string>
#include <unordered_set>

namespace Aether {
    struct GameState {
        unsigned int day;
        unsigned int habitability;
        std::unordered_set<std::string> knownElements;
    };

    struct Player {
        std::string name;
        float hp;
        float maxHp;
    };
}; // namespace Aether
