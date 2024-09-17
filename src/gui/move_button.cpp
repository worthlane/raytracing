#include "gui/move_button.hpp"

MoveLightButton::MoveLightButton(const size_t length, const size_t width, const Dot& upper_left,
                                Scene::LightSource* light, const Vector3& delta,
                                const char* default_img, const char* click_img) :
    AButton(length, width, upper_left),
    light_(light),
    delta_(delta)
{
    default_.loadFromFile(default_img);
    pressed_.loadFromFile(click_img);
}

// ----------------------------------------------------------------------

MoveLightButton::~MoveLightButton()
{
    light_ = nullptr;
}

// ----------------------------------------------------------------------

bool MoveLightButton::on_default(Graphics::Window& window)
{
    DRAW_BUTTON(window, default_);
    return false;
}

// ----------------------------------------------------------------------

bool MoveLightButton::on_click(Graphics::Window& window)
{
    DRAW_BUTTON(window, pressed_);

    light_->set_center(light_->get_center() + delta_);
    return true;
}

// ---------------------------------------------------------------------

bool MoveLightButton::on_hover(Graphics::Window& window)
{
    DRAW_BUTTON(window, default_);
    return false;
}

// ----------------------------------------------------------------------

bool MoveLightButton::on_release(Graphics::Window& window)
{
    DRAW_BUTTON(window, default_);
    return false;
}
