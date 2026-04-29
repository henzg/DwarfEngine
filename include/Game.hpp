#pragma once
#include "Engine.hpp"
#include "Component.hpp"
#include "Log.hpp"
#include <format>

namespace Dwarf {
    class Game {
      public:
        Game(Engine& engine);
        ~Game() = default;

        void Update(float dt);

      private:
        Engine& m_Engine;
        EntityID m_Player, m_Enemy, m_Tree;

      private:
        void Init();
        void RegisterEvents();
        void CreateEntities();
    };
} // namespace Dwarf
