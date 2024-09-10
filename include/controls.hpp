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
        Button(const size_t length, const size_t width, const Dot& upper_left);
        ~Button();

        bool is_pointed(const Window& window);

        ButtonCondition condition(const Window& window);


    private:

    size_t width_, length_;
    Dot upper_left_;

    ButtonCondition cond_ = ButtonCondition::DEFAULT;

};


#endif // _CONTROLS_HPP_
