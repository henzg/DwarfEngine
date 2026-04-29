#pragma once
#include "Registry.hpp"
#include "Dispatcher.hpp"
#include "Event.hpp"
#include "Log.hpp"

namespace Dwarf {
    class Engine {
      public:
        Engine() {
            LOG_INFO("Dwarf Engine Spinning Up!");
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
        auto View() {
            return m_ECS.view<T>();
        }

        void Run();

        void setRunning(bool running) { m_Running = running; }

        void SetUpdateCallback(std::function<void(float)> callback) {
            m_UpdateCallback = callback;
        };

      private:
        Registry m_ECS;
        Dispatcher m_Dispatcher;

        bool m_Running = true;
        int m_KeyCode;

        float m_DeltaTime;
        float m_FPS = 60;

        std::function<void(float)> m_UpdateCallback;
    };

} // namespace Dwarf
