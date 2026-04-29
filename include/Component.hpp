#pragma once
/*Library of component definitions*/

namespace Dwarf {

    struct PositionComponent {
        float x, y;
    };

    struct HealthComponent {
        float hp, maxHp;
    };

    struct VelocityComponent {
        float dx, dy;
    };

} // namespace Dwarf
