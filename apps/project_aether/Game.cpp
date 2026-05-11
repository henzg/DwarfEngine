#include "Game.hpp"
#include "CommandTypes.hpp"
#include "Component.hpp"
#include "ElementRegistry.hpp"

namespace Aether {
    Game::Game(Dwarf::Engine& engine) : m_Engine(engine) { Init(); }

    // ----- Game Helper Functions -----
    void Game::Update(float dt) {
        for (auto [id, hp] : m_Engine.View<Aether::HealthComponent>()) {
            hp.hp += 2.0f * dt;
            if (hp.hp > hp.maxHp)
                hp.hp = hp.maxHp;
        }
    }

    CommandResult Game::ExecuteCommand(ParseCommand command) {
        auto it = m_CommandRegistry.find(command.name);
        if (it != m_CommandRegistry.end()) {
            return it->second.callback(command);
        }
        ParseCommand err = ParseCommand {"unknown", {}};
        it               = m_CommandRegistry.find(err.name);
        return it->second.callback(err);
    }

    // ----- Game Inits -----
    void Game::Init() {

        RegisterEvents();
        CreateEntities();
        CreateElementRegistry();
        InitCommands();
    }
    void Game::RegisterEvents() {
        m_Engine.SetUpdateCallback([this](float dt) { Update(dt); });

        m_Engine.Subscribe<Dwarf::LineEnteredEvent>([this](const Dwarf::LineEnteredEvent& e) {
            CommandResult r = ExecuteCommand(ParseCommand {.name = e.input, .args = {}});
            LOG_DEBUG(std::format("Command: {}", r.output));
            LOG_DEBUG(std::format("LINE: {}", e.input));
        });
    }
    void Game::CreateEntities() {
        m_PlayerID = m_Engine.NewEntity();
        auto enemy = m_Engine.NewEntity();
        auto tree  = m_Engine.NewEntity();
        m_Engine.AddComponent<Aether::PositionComponent>(m_PlayerID, {0.0f, 0.0f});
        m_Engine.AddComponent<Aether::HealthComponent>(m_PlayerID, {10.0f, 25.0f});
        m_Engine.AddComponent<Aether::PositionComponent>(enemy, {25.0f, 30.0f});
        m_Engine.AddComponent<Aether::HealthComponent>(enemy, {5.0f, 5.0f});
        m_Engine.AddComponent<Aether::PositionComponent>(tree, {45.f, 68.f});
    }

    void Game::CreateElementRegistry() {
        auto& ER = Aether::ElementRegistry::get();

        ER.registerElement({"Ferrite", {"structural", "solid"}, .0f, 1500.0f, {}, true});
        ER.registerElement(
            {"Cryonite", {"conductive", "solid", "low_temp_stable"}, .0f, -180.0f, {}, false});
        ER.registerElement({"Carbonit",
                            {"flammable", "carbon_based", "solid"},
                            .6f,
                            800.0f,
                            {"CO2", "Ash"},
                            false});
    }

    void Game::InitCommands() {
        m_CommandRegistry["help"] =
            Command {"help", "help", "List all available commands",
                     [this](const ParseCommand& cmd) -> CommandResult {
                         if (!cmd.args.empty()) {
                             return {"Usage: help", false};
                         }
                         std::string out = "Available commands:\n";
                         for (const auto& [name, command] : m_CommandRegistry) {
                             out += " - " + command.name + ": " + command.desc + "\n";
                         }
                         return {out, true};
                     }};

        m_CommandRegistry["quit"] = Command {"quit", "quit", "Exits Application",
                                             [this](const ParseCommand& cmd) -> CommandResult {
                                                 if (!cmd.args.empty()) {
                                                     return {"quit: help", false};
                                                 }
                                                 std::string out = "Quitting application\n";
                                                 m_Engine.Emit(Dwarf::WindowCloseEvent {});
                                                 return {out, true};
                                             }};

        m_CommandRegistry["status"] = Command {
            "status", "status", "Current Player Stats",
                [this](const ParseCommand& cmd)
                    -> CommandResult {
                    if (!cmd.args.empty()) {
                        return {"status: help", false};
                    }
                    std::string out = ""
                }

                       m_CommandRegistry["unknown"] =
                           Command {"unknown", "unknown", "Command unknown",
                                    [this](const ParseCommand& cmd) -> CommandResult {
                                        std::string out = "Unknown Command typed\n";
                                        return {out, true};
                                    }};
        }

    } // namespace Aether
