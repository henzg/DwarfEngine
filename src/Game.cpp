#include "Game.hpp"

namespace Dwarf {
    Game::Game(Engine& engine) : m_Engine(engine) { Init(); }

    // ----- Game Helper Functions -----
    void Game::Update(float dt) {
        for (auto [id, hp] : m_Engine.View<HealthComponent>()) {
            hp.hp += 2.0f * dt;
            if (hp.hp > hp.maxHp)
                hp.hp = hp.maxHp;
        }
    };
    // ----- Game Inits -----
    void Game::Init() {
        RegisterEvents();
        CreateEntities();
    }
    void Game::RegisterEvents() {
        m_Engine.Subscribe<Dwarf::KeyPressedEvent>([this](const Dwarf::KeyPressedEvent& e) {
            if (e.keyCode == 1)
                m_Engine.Emit(Dwarf::WindowCloseEvent {});
            else if (e.keyCode == 2) {
                for (const auto& [id, pos] : m_Engine.View<Dwarf::PositionComponent>()) {
                    LOG_DEBUG(std::format("Entity[{}] is at ({},{})", id, pos.x, pos.y));
                }
            } else if (e.keyCode == 3) {
                for (const auto& [id, hp] : m_Engine.View<Dwarf::HealthComponent>()) {
                    LOG_DEBUG(std::format("Entity[{}] HP:{:.2f}/{:.2f}", id, hp.hp, hp.maxHp));
                }
            } else {
                LOG_DEBUG(std::format("KEYCODE[{}]", e.keyCode));
            }
        });
        m_Engine.Subscribe<Dwarf::MouseMovedEvent>([](const Dwarf::MouseMovedEvent& e) {
            LOG_DEBUG(std::format("Mouse ({},{})", e.x, e.y));
        });
        m_Engine.SetUpdateCallback([this](float dt) { Update(dt); });
    }
    void Game::CreateEntities() {
        m_Player = m_Engine.NewEntity();
        m_Enemy  = m_Engine.NewEntity();
        m_Tree   = m_Engine.NewEntity();
        m_Engine.AddComponent<Dwarf::PositionComponent>(m_Player, {0.0f, 0.0f});
        m_Engine.AddComponent<Dwarf::HealthComponent>(m_Player, {10.0f, 25.0f});
        m_Engine.AddComponent<Dwarf::PositionComponent>(m_Enemy, {25.0f, 30.0f});
        m_Engine.AddComponent<Dwarf::HealthComponent>(m_Enemy, {5.0f, 5.0f});
        m_Engine.AddComponent<Dwarf::PositionComponent>(m_Tree, {45.f, 68.f});
    }

} // namespace Dwarf
