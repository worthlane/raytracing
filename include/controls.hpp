#ifndef _CONTROLS_HPP_
#define _CONTROLS_HPP_

#include "visual.hpp"

Vector2 get_mouse_position(const Window& window);


enum class ButtonCondition
{
    DEFAULT,
    PRESSED,
    RELEASED
};

class Button
{
    public:
        Button(const size_t length, const size_t width, const Dot& upper_left, void (*action)(void*),
               const char* default_image, const char* pressed_image);
        ~Button();

        bool is_pointed(const Window& window);

        ButtonCondition update_condition(Window& window, void* params);


    private:

    size_t width_, length_;
    Dot upper_left_;

    sf::Texture default_;
    sf::Texture pressed_;

    void (*action_)(void*);

    ButtonCondition cond_ = ButtonCondition::DEFAULT;

};

void default_action(void* params);


#endif // _CONTROLS_HPP_
