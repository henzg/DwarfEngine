#pragma once
#include "Engine.hpp"
#include "Component.hpp"

namespace Dwarf {
    class Game {
      public:
        Game(Engine& engine) : m_Engine(engine) {
            m_Engine.Subscribe<Dwarf::KeyPressedEvent>([this](const Dwarf::KeyPressedEvent& e) {
                if (e.keyCode == 1)
                    m_Engine.Emit(Dwarf::WindowCloseEvent {});
                else if (e.keyCode == 2) {
                    for (const auto& [id, pos] : m_Engine.View<Dwarf::PositionComponent>()) {
                        std::cout << id << ": " << pos.x << "," << pos.y << "\n";
                    }
                } else if (e.keyCode == 3) {
                    for (const auto& [id, hp] : m_Engine.View<Dwarf::HealthComponent>()) {
                        std::cout << "ID: " << id << "|HP: " << hp.hp << "|MAXHP: " << hp.maxHp
                                  << "\n";
                    }
                } else {
                    std::cout << "KEYCODE: " << e.keyCode << "\n";
                }
            });
            m_Engine.Subscribe<Dwarf::MouseMovedEvent>([](const Dwarf::MouseMovedEvent& e) {
                std::cout << "MouseX: " << e.x << ", MouseY: " << e.y << "\n";
            });

            m_Player = m_Engine.NewEntity();
            m_Enemy  = m_Engine.NewEntity();
            m_Tree   = m_Engine.NewEntity();
            m_Engine.AddComponent<Dwarf::PositionComponent>(m_Player, {0.0f, 0.0f});
            m_Engine.AddComponent<Dwarf::HealthComponent>(m_Player, {10.0f, 25.0f});
            m_Engine.AddComponent<Dwarf::PositionComponent>(m_Enemy, {25.0f, 30.0f});
            m_Engine.AddComponent<Dwarf::HealthComponent>(m_Enemy, {5.0f, 5.0f});
            m_Engine.AddComponent<Dwarf::PositionComponent>(m_Tree, {45.f, 68.f});
        }
        ~Game() = default;

      private:
        Engine& m_Engine;
        EntityID m_Player, m_Enemy, m_Tree;
    };
} // namespace Dwarf
