#include <SFML/Window/Mouse.hpp>

#include "controls.hpp"

// ----------------------------------------------------------------------

Button::Button(const size_t length, const size_t width,   const Dot& upper_left) :
                    length_(length),      width_(width), upper_left_(upper_left)
{}

// ----------------------------------------------------------------------

Button::~Button()
{
    length_ = NAN;
    width_  = NAN;
}

// ----------------------------------------------------------------------

bool Button::is_pointed(const Window& window)
{
    Dot mouse = get_mouse_position(window);

    size_t mouse_x = mouse.get_x();
    size_t mouse_y = mouse.get_y();

    size_t left_x  = upper_left_.get_x();
    size_t right_x = left_x + length_;

    size_t upper_y = upper_left_.get_y();
    size_t lower_y = upper_y + width_;

    if ((left_x  <= mouse_x && mouse_x <= right_x) &&
        (upper_y <= mouse_y && mouse_y <= lower_y))
        return true;
    else
        return false;
}

// ----------------------------------------------------------------------

ButtonCondition Button::condition(const Window& window) // TODO
{
    ButtonCondition cond = ButtonCondition::DEFAULT;

    return cond;
}

// ----------------------------------------------------------------------

Vector2 get_mouse_position(const Window& window)
{
    sf::Vector2i vector = sf::Mouse::getPosition(window.window_);

    size_t x = vector.x;
    size_t y = vector.y;

    static const size_t Y_SHIFT = 0;
    static const size_t X_SHIFT = 0;

    Vector2 pos = {x - X_SHIFT, y - Y_SHIFT};

    return pos;
}
