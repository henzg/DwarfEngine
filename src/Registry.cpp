#include "Registry.hpp"

namespace Dwarf {

    EntityID Registry::createEntity() {
        EntityID currEID = m_NextEID;
        m_NextEID++;
        return currEID;
    }
} // namespace Dwarf
