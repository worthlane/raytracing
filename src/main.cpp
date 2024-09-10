#include <SFML/Graphics.hpp>

#include "vectors.hpp"
#include "visual.hpp"
#include "controls.hpp"

static const double DELTA_ANGLE = 1e-4;

static const size_t LENGTH = 1280;
static const size_t WIDTH  = 720;

static const double SCALE  = 0.05;

static const Vector2 NULL_VECTOR = {0, 0};

int main()
{
    Vector2 vec = {0, 0};
    Vector2 vec2 = {3, 5};
    Vector2 vec4 = {-9, 9};

    Vector3 vector = {7, 7, 9};

    RectangleSystem system = {LENGTH, WIDTH, SCALE, {0, 0}};

    Window window = {system, "Sphere"};

    LightSource light  = {{-5, 0, 10}, WHITE_PIXEL};
    LightSource light2 = {{9, 9, 0}, WHITE_PIXEL};

    Sphere sphere =  {system, 3, {0, -7}, RED_PIXEL};
    Sphere sphere2 = {system, 3, {0, 0}, BLUE_PIXEL};
    Sphere sphere3 = {system, 3, {0, 7}, WHITE_PIXEL};

    Button but = {20, 10, {100, 100}};

    double scale = SCALE;

    //sphere.render_sphere();
    sphere.add_light(light);
    sphere2.add_light(light);
    sphere3.add_light(light);

    sphere.add_light(light2);
    sphere2.add_light(light2);
    sphere3.add_light(light2);
    //sphere.add_light(light2);
    //sphere.add_light(light3);

    while (window.is_open())
    {
        window.closure_check();

        window.clear();

        window.draw_sphere(sphere);
        window.draw_sphere(sphere2);
        window.draw_sphere(sphere3);

        Vector2 mouse = get_mouse_position(window);
        mouse.print();

        printf("%d\n", but.is_pointed(window));

        window.display();
    }
}
