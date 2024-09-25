#include <iostream>

#include "gui/actions.hpp"

#include "graphics/pixels_array.hpp"

static const sf::Keyboard::Key SWITCH_SYMBOL = sf::Keyboard::Key::LShift;

// ----------------------------------------------------------------------

LightMoveAction::LightMoveAction(Scene::LightSource* default_light, Scene::LightSource* secondary_light, const Vector3& delta) :
    default_light_(default_light),
    secondary_light_(secondary_light),
    delta_(delta)
{
}

// ----------------------------------------------------------------------

LightMoveAction::~LightMoveAction()
{
    default_light_   = nullptr;
    secondary_light_ = nullptr;
}

// ----------------------------------------------------------------------

void LightMoveAction::operator()(Graphics::Event& event)
{
    Scene::LightSource* source = nullptr;

    if (sf::Keyboard::isKeyPressed(SWITCH_SYMBOL))
        source = secondary_light_;
    else
        source = default_light_;

    source->set_center(source->get_center() + delta_);
}

// ----------------------------------------------------------------------

LightColorAction::LightColorAction(Scene::LightSource* default_light, Scene::LightSource* secondary_light, const Vector3& color) :
    default_light_(default_light),
    secondary_light_(secondary_light),
    color_(color)
{
}

// ----------------------------------------------------------------------

LightColorAction::~LightColorAction()
{
    default_light_   = nullptr;
    secondary_light_ = nullptr;
}

// ----------------------------------------------------------------------

void LightColorAction::operator()(Graphics::Event& event)
{
    if (sf::Keyboard::isKeyPressed(SWITCH_SYMBOL))
        secondary_light_->set_color(color_);
    else
        default_light_->set_color(color_);
}

