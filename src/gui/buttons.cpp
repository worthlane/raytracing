#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

#include "gui/buttons.hpp"

static const double MASK_DELTA = 0.001;

const char* RED_SUBSCRIBE_BUTTON  = "assets/textures/button_default.png";
const char* GRAY_SUBSCRIBE_BUTTON = "assets/textures/button_pressed.png";

//static const std::chrono::milliseconds ANIMATION_TIME = 3000;

// ----------------------------------------------------------------------

AButton::AButton(const size_t length, const size_t width, const Dot& upper_left,
                const sf::Texture def, const sf::Texture hovered, const sf::Texture pressed, const sf::Texture released, Action* action) :
                length_(length), width_(width), upper_left_(upper_left),
                default_(def), hovered_(hovered), pressed_(pressed), released_(released), action_(action)
{
}

// ----------------------------------------------------------------------

AButton::AButton(const size_t length, const size_t width, const Dot& upper_left, Action* action) :
                length_(length), width_(width), upper_left_(upper_left), action_(action)
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

bool AButton::update(Graphics::Window& window, Graphics::Event& event)
{
    switch (cond_)
    {
        case ButtonCondition::DEFAULT:
            this->handle_default_(window);
            return this->on_default(window, event);

        case ButtonCondition::HOVERED:
            this->handle_hover_(window);
            return this->on_hover(window, event);

        case ButtonCondition::PRESSED:
            this->handle_click_(window);
            return this->on_click(window, event);

        case ButtonCondition::RELEASED:
            this->handle_release_(window);
            return this->on_release(window, event);

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

bool AButton::on_default(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, default_);
    return false;
}

// ----------------------------------------------------------------------

bool AButton::on_click(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, pressed_);
    return false;
}

// ---------------------------------------------------------------------

bool AButton::on_hover(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, hovered_);
    return false;
}

// ----------------------------------------------------------------------

bool AButton::on_release(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, released_);
    return false;
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

AnimatedButton::AnimatedButton(const size_t length, const size_t width, const Dot& upper_left, Action* action, const Vector3& color) :
                AButton(length, width, upper_left, action), interact_time_(0)
{
    mask_brightness_ = 0;

    PixelCondition but_color = {color.get_x(), color.get_y(), color.get_z(), RGB_MAX};
    PixelCondition hov_color = {RGB_MAX - color.get_x(), RGB_MAX - color.get_y(), RGB_MAX - color.get_z(), RGB_MAX};

    Pixels def_pixels(length, width);
    def_pixels.paint_array(but_color);

    default_.create(length, width);
    default_.update(def_pixels.get_array());

    released_ = default_;

    Pixels hov_pixels(length, width);
    hov_pixels.paint_array(but_color);
    hov_pixels.paint_frame(hov_color, length, width, 0.1);

    hovered_.create(length, width);
    hovered_.update(hov_pixels.get_array());

    pressed_ = hovered_;
}

// ----------------------------------------------------------------------

AnimatedButton::~AnimatedButton()
{}

// ----------------------------------------------------------------------

bool AnimatedButton::on_default(Graphics::Window& window, Graphics::Event& event)
{
    /*std::chrono::steady_clock::time_point moment = std::chrono::steady_clock::now();
    std::chrono::milliseconds delta = moment - last_update_;
    last_update_ = moment;*/

    if (mask_brightness_ > 0)
    {
        mask_brightness_ -= MASK_DELTA;
    }

    DRAW_BUTTON_WITH_MASK(window, default_, hovered_, mask_brightness_);

    return false;
}

// ----------------------------------------------------------------------

bool AnimatedButton::on_hover(Graphics::Window& window, Graphics::Event& event)
{
    if (mask_brightness_ < 1)
    {
        mask_brightness_ += MASK_DELTA;
    }

    DRAW_BUTTON_WITH_MASK(window, default_, hovered_, mask_brightness_);

    return false;
}

// ----------------------------------------------------------------------

bool AnimatedButton::on_click(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, pressed_);

    mask_brightness_ = 1;

    return false;
}

// ----------------------------------------------------------------------

bool AnimatedButton::on_release(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, released_);

    (*action_)(event);

    return true;
}

// ----------------------------------------------------------------------

SubscribeButton::SubscribeButton(const size_t length, const size_t width, const Dot& upper_left, Action* action) :
    AButton(length, width, upper_left, action)
{
    default_.loadFromFile(RED_SUBSCRIBE_BUTTON);
    pressed_.loadFromFile(GRAY_SUBSCRIBE_BUTTON);

    hovered_ = default_;
    released_ = pressed_;
}

// ----------------------------------------------------------------------

SubscribeButton::~SubscribeButton()
{
}

// ----------------------------------------------------------------------

bool SubscribeButton::on_click(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, pressed_);

    (*action_)(event);

    return true;
}

