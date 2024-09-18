#include "gui/color_button.hpp"

#include "graphics/pixels_array.hpp"

ColorLightButton::ColorLightButton(const size_t length, const size_t width, const Dot& upper_left,
                                   Scene::LightSource* light, const Vector3& color) :
    AButton(length, width, upper_left),
    light_(light),
    color_(color)
{
    PixelCondition but_color = {color.get_x(), color.get_y(), color.get_z(), RGB_MAX};
    PixelCondition hov_color = {RGB_MAX - color.get_x(), RGB_MAX - color.get_y(), RGB_MAX - color.get_z(), RGB_MAX};

    Pixels def_pixels(length, width);
    def_pixels.paint_array(but_color);

    default_.create(length, width);
    default_.update(def_pixels.get_array());

    Pixels hov_pixels(length, width);
    hov_pixels.paint_array(but_color);
    hov_pixels.paint_frame(hov_color, length, width, 0.1);

    hovered_.create(length, width);
    hovered_.update(hov_pixels.get_array());
}

// ----------------------------------------------------------------------

ColorLightButton::~ColorLightButton()
{
    light_ = nullptr;
}

// ----------------------------------------------------------------------

bool ColorLightButton::on_default(Graphics::Window& window)
{
    DRAW_BUTTON(window, default_);
    return false;
}

// ----------------------------------------------------------------------

bool ColorLightButton::on_click(Graphics::Window& window)
{
    DRAW_BUTTON(window, default_);
    return false;
}

// ---------------------------------------------------------------------

bool ColorLightButton::on_hover(Graphics::Window& window)
{
    DRAW_BUTTON(window, hovered_);
    return false;
}

// ----------------------------------------------------------------------

bool ColorLightButton::on_release(Graphics::Window& window)
{
    DRAW_BUTTON(window, default_);

    light_->set_color(color_);
    return true;
}
