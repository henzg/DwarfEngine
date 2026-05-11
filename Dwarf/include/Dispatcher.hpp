#pragma once

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include "DynamicArray.hpp"
#include <any>
#include <functional>

namespace Dwarf {
    class Dispatcher {
      public:
        Dispatcher() {}
        ~Dispatcher() = default;

        template <typename T>
        void subscribe(std::function<void(const T&)> callback) {
            auto wrapper = [callback](const std::any& event) {
                callback(std::any_cast<const T&>(event));
            };
            m_Listeners[std::type_index(typeid(T))].push_back(wrapper);
        }
        template <typename T>
        void emit(const T& event) {
            auto const it = m_Listeners.find(std::type_index(typeid(T)));
            if (it != m_Listeners.end()) {
                for (const auto& i : it->second) {
                    i(std::any(event));
                }
            }
        }

      private:
        std::unordered_map<std::type_index, DynamicArray<std::function<void(const std::any&)>>>
            m_Listeners;
    };
} // namespace Dwarf
