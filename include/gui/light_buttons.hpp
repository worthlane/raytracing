#ifndef _LIGHT_BUTTONS_HPP_
#define _LIGHT_BUTTONS_HPP_

#include "gui/controls.hpp"
#include "scene/light.hpp"
#include "maths/vectors.hpp"

class ColorLightButton : public AButton
{
    public:
        ColorLightButton(const size_t length, const size_t width, const Dot& upper_left,
                        Scene::LightSource* default_light, Scene::LightSource* secondary_light,
                        const Vector3& color);
        virtual ~ColorLightButton();

        bool on_default(Graphics::Window& window) override;
        bool on_click(Graphics::Window& window) override;
        bool on_hover(Graphics::Window& window) override;
        bool on_release(Graphics::Window& window) override;

        void operator()() override;

    private:

        Scene::LightSource* default_light_;
        Scene::LightSource* secondary_light_;

        Vector3 color_;

        sf::Texture default_;
        sf::Texture hovered_;

};

class MoveLightButton : public AButton
{
    public:
        MoveLightButton(const size_t length, const size_t width, const Dot& upper_left,
                        Scene::LightSource* default_light, Scene::LightSource* secondary_light, const Vector3& delta,
                        const char* default_img, const char* click_img);
        virtual ~MoveLightButton();

        bool on_default(Graphics::Window& window) override;
        bool on_click(Graphics::Window& window) override;
        bool on_hover(Graphics::Window& window) override;
        bool on_release(Graphics::Window& window) override;

        void operator()() override;

    private:

        Scene::LightSource* default_light_;
        Scene::LightSource* secondary_light_;

        Vector3 delta_;

        sf::Texture default_;
        sf::Texture pressed_;
};

#endif // _COLOR_BUTTON_HPP_
