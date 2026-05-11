#pragma once
#include "Dwarf/include/Dwarf.hpp"
#include "Dwarf/include/Log.hpp"
#include <unordered_map>
#include <vector>
#include <string>

namespace Aether {

    class ElementRegistry {
      public:
        struct ElementDefinition {
            std::string name;
            std::vector<std::string> properties; // flammable, conductive etc;
            float energyDensity = .0f;
            float meltingPoint  = .0f;
            std::vector<std::string> byproducts;
            bool knownCompound = false; // pre-identified or needs analysis
        };

        // element registry stuff
        static ElementRegistry& get() {
            static ElementRegistry instance;
            return instance;
        }

        ElementRegistry(const ElementRegistry&)            = delete;
        ElementRegistry& operator=(const ElementRegistry&) = delete;

        // Element definition stuff
        void registerElement(ElementDefinition def) { m_ElementDatabase[def.name] = def; }
        ElementDefinition* getElement(const std::string& name) {
            auto it = m_ElementDatabase.find(name);
            if (it != m_ElementDatabase.end())
                return &it->second;
            LOG_WARN(std::format("Element '{}' not found in db.", name));
            return nullptr;
        }

      private:
        ElementRegistry() {}
        std::unordered_map<std::string, ElementDefinition> m_ElementDatabase;
    };

} // namespace Aether
