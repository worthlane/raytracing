#ifndef _GR_LIB_HPP_
#define _GR_LIB_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "coord_system.hpp"
#include "objects.hpp"

class Visual
{
    public:
        Visual(const RectangleSystem& system, const char* name);
        ~Visual();

        bool is_open();
        void clear();
        void display();
        void close();
        void closure_check();

        Vector2 get_mouse_position();

        void draw_sphere(const Sphere& sphere);

    private:

        sf::RenderWindow window_;
        RectangleSystem  system_;

};

#endif // GR_LIB_HPP
