#include <iostream>

#include "gui/light_buttons.hpp"

#include "graphics/pixels_array.hpp"

static const sf::Keyboard::Key SWITCH_SYMBOL = sf::Keyboard::Key::LShift;

ColorLightButton::ColorLightButton(const size_t length, const size_t width, const Dot& upper_left,
                                   Scene::LightSource* default_light, Scene::LightSource* secondary_light, const Vector3& color) :
    AnimatedButton(length, width, upper_left),
    default_light_(default_light),
    secondary_light_(secondary_light),
    color_(color)
{
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

ColorLightButton::~ColorLightButton()
{
    default_light_   = nullptr;
    secondary_light_ = nullptr;
}

// ----------------------------------------------------------------------

void ColorLightButton::operator()(Graphics::Event& event)
{
    if (sf::Keyboard::isKeyPressed(SWITCH_SYMBOL))
        secondary_light_->set_color(color_);
    else
        default_light_->set_color(color_);
}

// =======================================

MoveLightButton::MoveLightButton(const size_t length, const size_t width, const Dot& upper_left,
                                Scene::LightSource* default_light, Scene::LightSource* secondary_light, const Vector3& delta,
                                const char* default_img, const char* click_img) :
    AButton(length, width, upper_left),
    default_light_(default_light),
    secondary_light_(secondary_light),
    delta_(delta)
{
    default_.loadFromFile(default_img);
    pressed_.loadFromFile(click_img);

    hovered_ = default_;
    released_ = pressed_;
}

// ----------------------------------------------------------------------

MoveLightButton::~MoveLightButton()
{
    default_light_   = nullptr;
    secondary_light_ = nullptr;
}

// ----------------------------------------------------------------------

bool MoveLightButton::on_default(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, default_);
    return false;
}

// ----------------------------------------------------------------------

bool MoveLightButton::on_click(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, pressed_);

    (*this)(event);

    return true;
}

// ---------------------------------------------------------------------

bool MoveLightButton::on_hover(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, hovered_);
    return false;
}

// ----------------------------------------------------------------------

bool MoveLightButton::on_release(Graphics::Window& window, Graphics::Event& event)
{
    DRAW_BUTTON(window, released_);
    return false;
}

// ----------------------------------------------------------------------

void MoveLightButton::operator()(Graphics::Event& event)
{
    Scene::LightSource* source = nullptr;

    if (sf::Keyboard::isKeyPressed(SWITCH_SYMBOL))
        source = secondary_light_;
    else
        source = default_light_;

    source->set_center(source->get_center() + delta_);
}
