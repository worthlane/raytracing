#ifndef _GR_LIB_HPP_
#define _GR_LIB_HPP_

#include <SFML/Graphics.hpp>

#include "coord_system.hpp"
#include "objects.hpp"

class Window
{
    public:
        Window(const RectangleSystem& system, const char* name);
        ~Window();

        bool is_open();
        void clear();
        void display();
        void close();
        void closure_check();

        void set_system(const RectangleSystem& system);

        Vector2 get_mouse_position();

        void draw_sphere(const Sphere& sphere);
        void draw(const sf::Sprite& sprite); // TODO convert

        sf::RenderWindow window_;

    private:
        RectangleSystem  system_;

};

#endif // GR_LIB_HPP
