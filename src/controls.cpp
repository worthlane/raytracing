#include <SFML/Window/Mouse.hpp>

#include "controls.hpp"

// ----------------------------------------------------------------------

Vector2 get_mouse_position() // TODO refactor
{
    sf::Vector2i vector = sf::Mouse::getPosition();

    double x = vector.x;
    double y = vector.y;

    static const size_t Y_SHIFT = 1800;
    static const size_t X_SHIFT = 0;

    Vector2 pos = {x - X_SHIFT, y - Y_SHIFT};

    pos.print();

    return pos;
}
