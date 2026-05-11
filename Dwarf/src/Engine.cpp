#include "Engine.hpp"

#include <chrono>

#include <sys/select.h>
#include <unistd.h>
#include <thread>

namespace Dwarf {
    EntityID Engine::NewEntity() { return m_ECS.createEntity(); }

    void Engine::Run() {

        auto lastTime = std::chrono::high_resolution_clock::now();
        while (m_Running) {
            // time
            auto currentTime = std::chrono::high_resolution_clock::now();
            m_DeltaTime      = std::chrono::duration<float>(currentTime - lastTime).count();

            if (m_CMDInputEnabled) {
                // select() - for input watch
                fd_set readfds;
                FD_ZERO(&readfds);              // clear the set
                FD_SET(STDIN_FILENO, &readfds); // watch stdin

                timeval timeout {0, 0};

                int result = select(1, &readfds, nullptr, nullptr, &timeout);
                if (result > 0) {
                    std::getline(std::cin, m_CMDInputStr);
                    Emit(LineEnteredEvent {m_CMDInputStr});
                }
            }

            // 60FPS control
            if (m_DeltaTime < 1.0f / m_FPS) {
                std::this_thread::sleep_for(std::chrono::duration<float>(1.0f / m_FPS) -
                                            std::chrono::duration<float>(m_DeltaTime));
            } else {
                LOG_WARN(std::format("FPS DROP"));
            }
            lastTime             = std::chrono::high_resolution_clock::now();
            auto actualFrameTime = std::chrono::duration<float>(lastTime - currentTime).count();
            // std::cout << "Actual Frame: " << actualFrameTime * 1000.0f << "ms\n";

            if (m_UpdateCallback)
                m_UpdateCallback(m_DeltaTime);
        }
    }
} // namespace Dwarf
