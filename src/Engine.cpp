#include "Engine.hpp"
namespace Dwarf {
    EntityID Engine::NewEntity() { return m_ECS.createEntity(); }

    void Engine::Run() {

        while (m_Running) {
            std::cout << "Keypress Sim: ";
            std::cin >> m_KeyCode;
            Emit(Dwarf::KeyPressedEvent {m_KeyCode});
        }
    }
} // namespace Dwarf
