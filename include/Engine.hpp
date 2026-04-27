#pragma once
#include "Registry.hpp"
#include "Dispatcher.hpp"
#include "Event.hpp"

namespace Dwarf {
    class Engine {
      public:
        Engine() {
            Subscribe<Dwarf::WindowCloseEvent>(
                [this](const Dwarf::WindowCloseEvent& e) { m_Running = false; });
        }
        ~Engine() = default;

        template <typename T>
        void Subscribe(std::function<void(const T&)> callback) {
            m_Dispatcher.subscribe<T>(callback);
        }
        template <typename T>
        void Emit(const T& event) {
            m_Dispatcher.emit(event);
        }

        EntityID NewEntity();

        template <typename T>
        void AddComponent(const EntityID& owner, const T& component) {
            m_ECS.addComponent<T>(owner, component);
        }

        template <typename T>
        Registry::View<T> View() {
            return m_ECS.view<T>();
        }

        void Run();

        void setRunning(bool running) { m_Running = running; }

      private:
        Registry m_ECS;
        Dispatcher m_Dispatcher;

        bool m_Running = true;
        int m_KeyCode;
    };

} // namespace Dwarf
