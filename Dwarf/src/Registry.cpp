#include "Registry.hpp"
#include <format>

namespace Dwarf {

    EntityID Registry::createEntity() {
        EntityID currEID = m_NextEID;
        m_NextEID++;
        return currEID;
    }
    void Registry::destroyEntity(const EntityID owner) {
        unsigned int removed_count = 0;
        for (auto& [type, innerMap] : m_Components) {
            auto removed = innerMap.erase(owner);
            if (removed > 0)
                removed_count++;
        }
        LOG_DEBUG(std::format("Removed {} components from ID[{}]", removed_count, owner));
    }
} // namespace Dwarf
