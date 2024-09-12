#ifndef _CONTROLS_HPP_
#define _CONTROLS_HPP_

#include <vector>

#include "graphics/visual.hpp"

Vector2 get_mouse_position(const Window& window);

enum class ButtonCondition
{
    DEFAULT,
    PRESSED,
    RELEASED
};

enum class ButtonType
{
    HOLD,
    RELEASE,
    DISABLED
};

class Button
{
    public:
        Button(const size_t length, const size_t width, const Dot& upper_left, const ButtonType type,
               void (*action)(void*), const char* default_image, const char* pressed_image);
        ~Button();

        bool is_hovered(const Window& window);

        ButtonCondition update_condition(Window& window, void* params);

    private:

        virtual void when_default_(Window& window, void* params, const bool is_hovered, const bool is_pressed);
        virtual void when_pressed_(Window& window, void* params, const bool is_hovered, const bool is_pressed);
        virtual void when_released_(Window& window, void* params, const bool is_hovered, const bool is_pressed);

    size_t width_, length_;
    Dot upper_left_;

    sf::Texture default_;
    sf::Texture pressed_;

    void (*action_)(void*);

    ButtonCondition cond_ = ButtonCondition::DEFAULT;
    ButtonType      type_ = ButtonType::DISABLED;

};

void default_action(void* params);

#endif // _CONTROLS_HPP_
