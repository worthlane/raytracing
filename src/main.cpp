#include <SFML/Graphics.hpp>

#include "vectors.hpp"
#include "visual.hpp"
#include "controls.hpp"

static const double DELTA_ANGLE = 1e-4;
static const size_t LENGTH = 1280;
static const size_t WIDTH  = 720;
static const double SCALE  = 0.05;

static const Vector2 NULL_VECTOR = {0, 0};

const char* DEFAULT_BUTTON = "assets/textures/button_default.png";
const char* PRESSED_BUTTON = "assets/textures/button_pressed.png";
const size_t BUTTON_LENGTH = 200;
const size_t BUTTON_WIDTH  = 80;

struct Scene
{
    Sphere sphere1;
    Sphere sphere2;
    Sphere sphere3;

    LightSource light1;
    LightSource light2;
};

void render_scene(const Scene& scene);

int main()
{
    RectangleSystem system = {LENGTH, WIDTH, SCALE, {0, 0}};
    Window          window = {system, "Sphere"};

    Vector3 light_pos = {-5, 0, 10};
    Vector3 delta_light = {0, 1, 0};

    LightSource light  = {{-5, 0, 10}, WHITE_PIXEL};
    LightSource light2 = {{9, 9, 0}, WHITE_PIXEL};

    Sphere sphere =  {system, 3, {0, -7}, RED_PIXEL};
    Sphere sphere2 = {system, 3, {0, 0}, BLUE_PIXEL};
    Sphere sphere3 = {system, 3, {0, 7}, WHITE_PIXEL};

    Scene scene = {sphere, sphere2, sphere3, light, light2};

    Button but = {BUTTON_LENGTH, BUTTON_WIDTH, {100, 100}, default_action, DEFAULT_BUTTON, PRESSED_BUTTON};

    double scale = SCALE;

    sphere.add_light(light);
    sphere2.add_light(light);
    sphere3.add_light(light);

    sphere.add_light(light2);
    sphere2.add_light(light2);
    sphere3.add_light(light2);

    while (window.is_open())
    {
        window.closure_check();

        window.clear();

        window.draw_sphere(sphere);
        window.draw_sphere(sphere2);
        window.draw_sphere(sphere3);

        Vector2 mouse = get_mouse_position(window);
        mouse.print();

        printf("%d %d\n", but.is_pointed(window), but.update_condition(window, nullptr));

        //but.update_condition(window, nullptr);

        /*light_pos = light_pos + delta_light;
        light.center = light_pos;

        sphere.clear();
        sphere2.clear();
        sphere3.clear();

        sphere.add_light(light);
        sphere2.add_light(light);
        sphere3.add_light(light);
        sphere.add_light(light2);
        sphere2.add_light(light2);
        sphere3.add_light(light2);*/



        window.display();
    }
}
