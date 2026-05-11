#pragma once

/*Class that acts as a component/entity blob storage*/

#include "Dwarf.hpp"
// #include "Component.hpp"
#include <unordered_map>
#include <any>
#include <typeinfo>
#include <typeindex>
#include "Log.hpp"
#include <format>

namespace Dwarf {

    class Registry {
      public:
        template <typename T, typename MapType>
        struct View {

            View(MapType* map) : m_Map(map) {}
            ~View() = default;

            template <typename IteratorType>
            struct Iterator {

                Iterator(IteratorType i) : it(i) {}
                ~Iterator() = default;
                std::pair<EntityID, T&> operator*() const {
                    return {it->first, *std::any_cast<T>(&it->second)};
                }
                Iterator& operator++() {
                    ++it;
                    return *this;
                }
                bool operator!=(const Iterator& other) const { return it != other.it; }

                IteratorType it;
            };
            static constexpr bool IsConst = std::is_const_v<MapType>;
            using MyIterator = std::conditional_t<IsConst, typename MapType::const_iterator,
                                                  typename MapType::iterator>;
            using Iter = Iterator<MyIterator>;

            Iter begin() {
                if (!m_Map)
                    return end();
                return Iter {m_Map->begin()};
            }
            Iter end() {
                if (!m_Map) {
                    static MapType empty;
                    return Iter {empty.end()};
                }
                return Iter {m_Map->end()};
            }

            MapType* m_Map;
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

        void destroyEntity(const EntityID owner);

        template <typename T>
        View<T, std::unordered_map<EntityID, std::any>> view() {
            auto it = m_Components.find(std::type_index(typeid(T)));
            if (it != m_Components.end())
                return {&it->second};
            return {nullptr};
        }
        template <typename T>
        View<T, const std::unordered_map<EntityID, std::any>> view() const {
            auto it = m_Components.find(std::type_index(typeid(T)));
            if (it != m_Components.end())
                return {&it->second};
            return {nullptr};
        }

      private:
        EntityID m_NextEID;

      private:
        std::unordered_map<std::type_index, std::unordered_map<EntityID, std::any>> m_Components;

      private:
    };

} // namespace Dwarf
