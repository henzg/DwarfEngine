#pragma once

#include <string>

namespace Dwarf {
    struct KeyPressedEvent {
        int keyCode;
    };

    struct MouseMovedEvent {
        float x, y;
    };

    struct WindowCloseEvent {};

    struct LineEnteredEvent {
        std::string input;
    };
} // namespace Dwarf
