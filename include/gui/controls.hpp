#ifndef _CONTROLS_HPP_
#define _CONTROLS_HPP_

#include <vector>

#include "graphics/visual.hpp"

Vector2 get_mouse_position(const Graphics::Window& window);

enum class ButtonCondition
{
    DEFAULT,
    HOVERED,
    PRESSED,
    RELEASED
};

enum class ButtonType
{
    HOLD,
    RELEASE,
    DISABLED
};

class AButton
{
    public:
        AButton(const size_t length, const size_t width, const Dot& upper_left);
        ~AButton();

        virtual bool on_default(Graphics::Window& window) = 0;
        virtual bool on_hover(Graphics::Window& window)   = 0;
        virtual bool on_click(Graphics::Window& window)   = 0;
        virtual bool on_release(Graphics::Window& window) = 0;

        virtual void operator()() = 0;

        bool is_hovered(const Graphics::Window& window);

        bool update(Graphics::Window& window);

    protected:
        size_t width_, length_;
        Dot upper_left_;

        ButtonCondition cond_ = ButtonCondition::DEFAULT;

        void handle_default_(Graphics::Window& window);
        void handle_hover_(Graphics::Window& window);
        void handle_click_(Graphics::Window& window);
        void handle_release_(Graphics::Window& window);
};

#define DRAW_BUTTON(window, texture)    do                              \
                                        {                               \
                                            Graphics::Sprite sprite;    \
                                            sprite.set_texture(texture);\
                                            sprite.set_position(upper_left_.get_x(), upper_left_.get_y());  \
                                            window.draw(sprite);                                            \
                                        } while(0)

void default_action(void* params);

#endif // _CONTROLS_HPP_
