#include <SFML/Graphics.hpp>
#include <assert.h>

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

void render_scene(Scene& scene);

void upper_light1(void* scene);
void lower_light1(void* scene);
void righter_light1(void* scene);
void lefter_light1(void* scene);

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

    Button up_but = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 100},
                     upper_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    Button low_but = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 300},
                     lower_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    Button right_but = {BUTTON_LENGTH, BUTTON_WIDTH, {300, 200},
                        righter_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    Button left_but = {BUTTON_LENGTH, BUTTON_WIDTH, {50, 200},
                       lefter_light1, DEFAULT_BUTTON, PRESSED_BUTTON};



    double scale = SCALE;

    render_scene(scene);

    /*sphere.add_light(light);
    sphere2.add_light(light);
    sphere3.add_light(light);

    sphere.add_light(light2);
    sphere2.add_light(light2);
    sphere3.add_light(light2);*/

    while (window.is_open())
    {
        window.closure_check();

        window.clear();

        window.draw_sphere(sphere);
        window.draw_sphere(sphere2);
        window.draw_sphere(sphere3);

        up_but.update_condition(window, &scene);
        low_but.update_condition(window, &scene);
        right_but.update_condition(window, &scene);
        left_but.update_condition(window, &scene);

        /*Vector2 mouse = get_mouse_position(window);
        mouse.print();

        printf("%d %d\n", but.is_pointed(window), but.update_condition(window, &scene));*/

        window.display();
    }
}

// ----------------------------------------------------------

void render_scene(Scene& scene)
{
    scene.sphere1.clear();
    scene.sphere2.clear();
    scene.sphere3.clear();

    scene.sphere1.add_light(scene.light1);
    scene.sphere2.add_light(scene.light1);
    scene.sphere3.add_light(scene.light1);

    scene.sphere1.add_light(scene.light2);
    scene.sphere2.add_light(scene.light2);
    scene.sphere3.add_light(scene.light2);
}

// ----------------------------------------------------------

void upper_light1(void* scene_ptr)
{
    assert(scene_ptr);

    Scene* scene = (Scene*) scene_ptr;

    static const Vector3 UPPERLIGHT_DELTA = {0, 1, 0};
    scene->light1.center = scene->light1.center + UPPERLIGHT_DELTA;

    render_scene(*scene);
}

// ----------------------------------------------------------

void lower_light1(void* scene_ptr)
{
    assert(scene_ptr);

    Scene* scene = (Scene*) scene_ptr;

    static const Vector3 LOWERLIGHT_DELTA = {0, -1, 0};
    scene->light1.center = scene->light1.center + LOWERLIGHT_DELTA;

    render_scene(*scene);
}

// ----------------------------------------------------------

void righter_light1(void* scene_ptr)
{
    assert(scene_ptr);

    Scene* scene = (Scene*) scene_ptr;

    static const Vector3 RIGHTERLIGHT_DELTA = {1, 0, 0};
    scene->light1.center = scene->light1.center + RIGHTERLIGHT_DELTA;

    render_scene(*scene);
}

// ----------------------------------------------------------

void lefter_light1(void* scene_ptr)
{
    assert(scene_ptr);

    Scene* scene = (Scene*) scene_ptr;

    static const Vector3 LEFTERLIGHT_DELTA = {-1, 0, 0};
    scene->light1.center = scene->light1.center + LEFTERLIGHT_DELTA;

    render_scene(*scene);
}


