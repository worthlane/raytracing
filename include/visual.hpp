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

        void draw_line(const Dot& start_dot, const Dot& end_dot, const sf::Color color);
        void draw_dot(const Dot& dot, const sf::Color color);
        void draw_free_vector(const Dot& end_point, const sf::Color color);
        void draw_vector(const Dot& start_point, const Vector2& vector, const sf::Color color); // TODO rename

        void draw_sphere(const Sphere& sphere);

    private:

        sf::RenderWindow window_;
        RectangleSystem  system_;

};

#endif // GR_LIB_HPP
