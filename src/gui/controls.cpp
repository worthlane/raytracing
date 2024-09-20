#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

#include "gui/controls.hpp"


// ----------------------------------------------------------------------

AButton::AButton(const size_t length, const size_t width, const Dot& upper_left,
                const sf::Texture def, const sf::Texture hovered, const sf::Texture pressed, const sf::Texture released) :
                length_(length), width_(width), upper_left_(upper_left),
                default_(def), hovered_(hovered), pressed_(pressed), released_(released)
{
}

// ----------------------------------------------------------------------

AButton::AButton(const size_t length, const size_t width, const Dot& upper_left) :
                length_(length), width_(width), upper_left_(upper_left)
{
}

// ----------------------------------------------------------------------

AButton::~AButton()
{
    length_ = NAN;
    width_  = NAN;
}

// ----------------------------------------------------------------------

bool AButton::is_hovered(const Graphics::Window& window)
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

bool AButton::update(Graphics::Window& window)
{
    switch (cond_)
    {
        case ButtonCondition::DEFAULT:
            this->handle_default_(window);
            return this->on_default(window);

        case ButtonCondition::HOVERED:
            this->handle_hover_(window);
            return this->on_hover(window);

        case ButtonCondition::PRESSED:
            this->handle_click_(window);
            return this->on_click(window);

        case ButtonCondition::RELEASED:
            this->handle_release_(window);
            return this->on_release(window);

        default:

            cond_ = ButtonCondition::DEFAULT;
            return false;
    }
}

// ----------------------------------------------------------------------

void AButton::handle_default_(Graphics::Window& window)
{
    bool is_hovered = this->is_hovered(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (is_hovered)
        cond_ = ButtonCondition::HOVERED;

    if (is_hovered && is_pressed)
        cond_ = ButtonCondition::PRESSED;
}

// ----------------------------------------------------------------------

void AButton::handle_hover_(Graphics::Window& window)
{
    bool is_hovered = this->is_hovered(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (!is_hovered)
    {
        cond_ = ButtonCondition::DEFAULT;
    }

    if (is_hovered && is_pressed)
        cond_ = ButtonCondition::PRESSED;
}


// ----------------------------------------------------------------------

void AButton::handle_click_(Graphics::Window& window)
{
    bool is_hovered = this->is_hovered(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (!is_pressed && is_hovered)
        cond_ = ButtonCondition::RELEASED;
    else if (!is_hovered)
        cond_ = ButtonCondition::DEFAULT;
}

// ----------------------------------------------------------------------

void AButton::handle_release_(Graphics::Window& window)
{
    bool is_hovered = this->is_hovered(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    cond_ = ButtonCondition::DEFAULT;
}

// ----------------------------------------------------------------------

Vector2 get_mouse_position(const Graphics::Window& window)
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

// ----------------------------------------------------------------------

/*AnimatedButton::AnimatedButton(const size_t length, const size_t width, const Dot& upper_left) :
                AButton(length, width, upper_left), std_color_(std_color), mask_color_(mask_color)
{
    mask_brightness_ = 0;
}

// ----------------------------------------------------------------------

~AnimatedButton::AnimatedButton()
{}

// ----------------------------------------------------------------------

bool AnimatedButton::on_default(Graphics::Window& window)
{
    if (mask_brightness_ > 0)
    {
        mask_brightness_ -= MASK_DELTA;
    }

    return false;
}

// ----------------------------------------------------------------------

bool AnimatedButton::on_hover(Graphics::Window& window)
{
    if (mask_brightness_ < 1)
    {
        mask_brightness_ += MASK_DELTA;
    }

    return false;
}

// ----------------------------------------------------------------------

bool AnimatedButton::on_click(Graphics::Window& window)
{
    return false;
}

// ----------------------------------------------------------------------

bool AnimatedButton::on_release(Graphics::Window& window)
{

    (*this)();

    return true;
}

// ----------------------------------------------------------------------

*/
