# DwarfEngine - mini Nova
This is a mini project that goes hand to hand with Nova and my journey to mastering C++. - It will be a much more lightweight project that is designed to show my progress in future subsystems for Novas engine and renderer. I will explore a lot of new topics and refine older ones in the DwarfEngine but trying to do so without exposing the code to as many external libraries as possible.

## Responsibility Boundaries

To keep Dwarf reusable as a lightweight engine, split ownership clearly:

### Engine provides
- Core loop and timing (`Run`, delta time, frame pacing).
- ECS primitives (entity IDs, component storage, typed views).
- Event/dispatcher infrastructure (subscribe/emit and base engine events).
- Logging and low-level utilities shared across projects.
- A clean API surface that multiple game/app projects can link against.

### Game provides
- Game rules and systems (combat, progression, crafting, survival logic).
- Content/data definitions (elements, recipes, item stats, balancing values).
- Input meaning and command handling (what a key/command does in gameplay terms).
- World setup and scenario logic (spawn rules, objectives, win/lose conditions).
- Anything specific to one game experience that another project would not reuse.
