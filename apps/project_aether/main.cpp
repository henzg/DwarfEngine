#include "Dwarf/include/Dwarf.hpp"
#include "Game.hpp"
#include "Dwarf/include/Engine.hpp"

int main() {
    Dwarf::Engine DE;
    Aether::Game game(DE);
    DE.Run();
}
