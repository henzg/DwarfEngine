#include "Dwarf.hpp"
#include "Game.hpp"
#include "Engine.hpp"

int main() {
    Dwarf::Engine DE;
    Dwarf::Game game(DE);
    DE.Run();
}
