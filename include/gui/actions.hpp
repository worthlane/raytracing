#ifndef _LIGHT_BUTTONS_HPP_
#define _LIGHT_BUTTONS_HPP_

#include "gui/buttons.hpp"
#include "scene/light.hpp"
#include "maths/vectors.hpp"

class LightColorAction : public Action
{
    public:
        LightColorAction(Scene::LightSource* default_light, Scene::LightSource* secondary_light,
                         const Vector3& color);
        ~LightColorAction();

        virtual void operator()(Graphics::Event& event) override;

    private:

        Scene::LightSource* default_light_;
        Scene::LightSource* secondary_light_;

        Vector3 color_;
};

class LightMoveAction : public Action
{
    public:

        LightMoveAction(Scene::LightSource* default_light, Scene::LightSource* secondary_light,
                        const Vector3& delta);
        ~LightMoveAction();

        virtual void operator()(Graphics::Event& event) override;

    private:

        Scene::LightSource* default_light_;
        Scene::LightSource* secondary_light_;

        Vector3 delta_;
};

#endif // _COLOR_BUTTON_HPP_
