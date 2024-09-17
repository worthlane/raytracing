#ifndef _COLOR_BUTTON_HPP_
#define _COLOR_BUTTON_HPP_

#include "gui/controls.hpp"
#include "scene/light.hpp"
#include "maths/vectors.hpp"

class ColorLightButton : public AButton
{
    public:
        ColorLightButton(const size_t length, const size_t width, const Dot& upper_left,
                        Scene::LightSource* light, const Vector3& color);
        virtual ~ColorLightButton();

        bool on_default(Graphics::Window& window) override;
        bool on_click(Graphics::Window& window) override;
        bool on_hover(Graphics::Window& window) override;
        bool on_release(Graphics::Window& window) override;

    private:

        Scene::LightSource* light_;
        Vector3 color_;

        sf::Texture default_;

};

#endif // _COLOR_BUTTON_HPP_
