#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

#include "gui/controls.hpp"


// ----------------------------------------------------------------------

Button::Button(const size_t length, const size_t width, const Dot& upper_left, const ButtonType type,
               void (*action)(void*), const char* default_image, const char* pressed_image) :
                    length_(length), width_(width), upper_left_(upper_left), action_(action)
{
	default_.loadFromFile(default_image);
    pressed_.loadFromFile(pressed_image);

    type_ = type;
}

// ----------------------------------------------------------------------

Button::~Button()
{
    length_ = NAN;
    width_  = NAN;
}

// ----------------------------------------------------------------------

bool Button::is_hovered(const Window& window)
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
    bool is_hovered = this->is_hovered(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    switch (cond_)
    {
        case ButtonCondition::DEFAULT:

            this->when_default_(window, params, is_hovered, is_pressed);
            break;

        case ButtonCondition::PRESSED:

            this->when_pressed_(window, params, is_hovered, is_pressed);
            break;

        case ButtonCondition::RELEASED:

            this->when_released_(window, params, is_hovered, is_pressed);
            break;

        default:

            cond_ = ButtonCondition::DEFAULT;
    }

    return cond_;
}

// ----------------------------------------------------------------------

void Button::when_default_(Window& window, void* params, const bool is_hovered, const bool is_pressed)
{
    Sprite default_sprite;
    default_sprite.set_texture(default_);
	default_sprite.set_position(upper_left_.get_x(), upper_left_.get_y());
    window.draw(default_sprite);

    if (is_hovered && is_pressed)
        cond_ = ButtonCondition::PRESSED;
}

// ----------------------------------------------------------------------

void Button::when_pressed_(Window& window, void* params, const bool is_hovered, const bool is_pressed)
{
    Sprite pressed_sprite;
    pressed_sprite.set_texture(pressed_);
	pressed_sprite.set_position(upper_left_.get_x(), upper_left_.get_y());
    window.draw(pressed_sprite);

    if (type_ == ButtonType::HOLD)
        action_(params);

    if (!is_pressed && is_hovered)
        cond_ = ButtonCondition::RELEASED;
    else if (!is_hovered)
        cond_ = ButtonCondition::DEFAULT;
}

// ----------------------------------------------------------------------

void Button::when_released_(Window& window, void* params, const bool is_hovered, const bool is_pressed)
{
    Sprite default_sprite;
    default_sprite.set_texture(default_);
	default_sprite.set_position(upper_left_.get_x(), upper_left_.get_y());
    window.draw(default_sprite);

    if (type_ == ButtonType::RELEASE)
        action_(params);

    cond_ = ButtonCondition::DEFAULT;
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
