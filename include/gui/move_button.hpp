#ifndef _MOVE_BUTTON_HPP_
#define _MOVE_BUTTON_HPP_

#include "gui/controls.hpp"
#include "scene/light.hpp"
#include "maths/vectors.hpp"

class MoveLightButton : public AButton
{
    public:
        MoveLightButton(const size_t length, const size_t width, const Dot& upper_left,
                        Scene::LightSource* light, const Vector3& delta,
                        const char* default_img, const char* click_img);
        virtual ~MoveLightButton();

        bool on_default(Graphics::Window& window) override;
        bool on_click(Graphics::Window& window) override;
        bool on_hover(Graphics::Window& window) override;
        bool on_release(Graphics::Window& window) override;

    private:

        Scene::LightSource* light_;
        Vector3 delta_;

        sf::Texture default_;
        sf::Texture pressed_;

};

#endif // _MOVE_BUTTON_HPP_
