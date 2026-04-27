#pragma once

/*Class that acts as a component/entity blob storage*/

#include "Dwarf.hpp"
// #include "Component.hpp"
#include <unordered_map>
#include <any>
#include <typeinfo>
#include <typeindex>

namespace Dwarf {

    class Registry {
      public:
        template <typename T>
        struct View {
            View(const std::unordered_map<EntityID, std::any>* componentMap)
                : componentMap(componentMap) {}
            ~View() = default;
            struct Iterator {
                Iterator(std::unordered_map<EntityID, std::any>::const_iterator it) : it(it) {}
                ~Iterator() = default;
                std::pair<EntityID, const T&> operator*() const {
                    return std::pair<EntityID, const T&> {it->first,
                                                          *std::any_cast<T>(&it->second)};
                }
                Iterator& operator++() {
                    ++it;
                    return *this;
                }
                bool operator!=(const Iterator& other) const { return it != other.it; }

                std::unordered_map<EntityID, std::any>::const_iterator it;
            };
            Iterator begin() {
                if (!componentMap)
                    return end();
                return Iterator {componentMap->begin()};
            }
            Iterator end() {
                if (!componentMap) {
                    static const std::unordered_map<EntityID, std::any> empty;
                    return Iterator {empty.end()};
                }
                return Iterator {componentMap->end()};
            }

            const std::unordered_map<EntityID, std::any>* componentMap;
        };

      public:
        Registry() : m_NextEID(0) {}
        ~Registry() = default;

        EntityID createEntity();

        template <typename T>
        void addComponent(EntityID owner, T component) {
            m_Components[std::type_index(typeid(T))][owner] = component;
        }

        template <typename T>
        T* getComponent(const EntityID owner) {
            auto const fit = m_Components.find(std::type_index(typeid(T)));
            if (fit != m_Components.end()) {
                auto const it = fit->second.find(owner);
                if (it != fit->second.end()) {
                    return std::any_cast<T>(&it->second);
                } else
                    return nullptr;
            }
            return nullptr;
        }

        template <typename T>
        View<T> view() {
            auto const it = m_Components.find(std::type_index(typeid(T)));
            if (it != m_Components.end())
                return View<T> {&it->second};
            return View<T> {nullptr};
        }

      private:
        EntityID m_NextEID;

      private:
        std::unordered_map<std::type_index, std::unordered_map<EntityID, std::any>> m_Components;

      private:
    };

} // namespace Dwarf
