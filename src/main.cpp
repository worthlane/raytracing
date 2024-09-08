#include <SFML/Graphics.hpp>

#include "vectors.hpp"
#include "visual.hpp"

static const double DELTA_ANGLE = 1e-4;

static const size_t LENGTH = 1000;
static const size_t WIDTH  = 640;

static const double SCALE  = 0.05;

static const Vector2 NULL_VECTOR = {0, 0};

int main()
{
    Vector2 vec = {0, 0};
    Vector2 vec2 = {3, 5};
    Vector2 vec4 = {-9, 9};
    Vector2 vec3 = (vec2.get_normal());

    Vector3 vector = {7, 7, 9};

    RectangleSystem system = {LENGTH, WIDTH, SCALE};

    Visual window = {system, "Sphere"};

    LightSource light  = {{0, 0, 100}};
    LightSource light2 = {{9, 9, 0}};
    LightSource light3 = {{9, -9, 0}};

    Sphere sphere = {system, 8, vec, RED_PIXEL};
    Sphere sphere2 = {system, 3, {-15, 0}, BLUE_PIXEL};
    //sphere.render_sphere();
    sphere.add_light(light);
    sphere.add_light(light2);
    //sphere2.add_light(light2);
    sphere.add_light(light3);

    while (window.is_open())
    {
        window.closure_check();

        window.clear();

        //vec2.rotate(DELTA_ANGLE);
        //window.draw_free_vector(vec2, sf::Color::Cyan);

        //Vector2 mouse = window.get_mouse_position();
        //window.draw_free_vector(mouse, sf::Color::Cyan);

        //window.draw_dot(NULL_VECTOR, sf::Color::Cyan);

        window.draw_sphere(sphere);
        window.draw_sphere(sphere2);
        //window.draw_sphere(sphere2);

        window.display();
    }
}
