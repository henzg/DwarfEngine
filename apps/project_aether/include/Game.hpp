#pragma once
#include "Dwarf/include/Dwarf.hpp"
#include "Dwarf/include/Engine.hpp"

#include "CommandTypes.hpp"
#include "GameState.hpp"
namespace Aether {
    class Game {
      public:
        Game(Dwarf::Engine& engine);
        ~Game() = default;

        void Update(float dt);

        CommandResult ExecuteCommand(ParseCommand command);

      private:
        Dwarf::Engine& m_Engine;
        Dwarf::EntityID m_PlayerID;
        Player m_Player;

        std::unordered_map<std::string, Aether::Command> m_CommandRegistry;

      private:
        void Init();
        void RegisterEvents();
        void CreateEntities();
        void CreateElementRegistry();
        void InitCommands();
    };
} // namespace Aether
