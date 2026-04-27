#pragma once

namespace Dwarf {
    struct KeyPressedEvent {
        int keyCode;
    };

    struct MouseMovedEvent {
        float x, y;
    };

    struct WindowCloseEvent {};
} // namespace Dwarf
