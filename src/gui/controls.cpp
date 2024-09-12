#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

#include "gui/controls.hpp"

// ----------------------------------------------------------------------

Button::Button(const size_t length, const size_t width,   const Dot& upper_left, void (*action)(void*),
               const char* default_texture, const char* pressed_texture) :
                    length_(length),      width_(width), upper_left_(upper_left), action_(action)
{
	default_.loadFromFile(default_texture);
    pressed_.loadFromFile(pressed_texture);
}

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

ButtonCondition Button::update_condition(Window& window, void* params)
{
    bool is_pointed = this->is_pointed(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    sf::Sprite default_sprite;
    default_sprite.setTexture(default_);
	default_sprite.setPosition(upper_left_.get_x(), upper_left_.get_y());

    sf::Sprite pressed_sprite;
    pressed_sprite.setTexture(pressed_);
	pressed_sprite.setPosition(upper_left_.get_x(), upper_left_.get_y());

    switch (cond_)
    {
        case ButtonCondition::DEFAULT:

            window.draw(default_sprite);

            if (is_pointed && is_pressed)
                cond_ = ButtonCondition::PRESSED;

            break;

        case ButtonCondition::PRESSED:

            window.draw(pressed_sprite);
            action_(params);

            if (!is_pressed && is_pointed)
                cond_ = ButtonCondition::RELEASED;
            else if (!is_pointed)
                cond_ = ButtonCondition::DEFAULT;

            break;

        case ButtonCondition::RELEASED:

            window.draw(default_sprite);
            //action_(params);

        default:

            cond_ = ButtonCondition::DEFAULT;
    }

    return cond_;
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

// ----------------------------------------------------------------------

void default_action(void* params)
{
    printf("action\n");
}
