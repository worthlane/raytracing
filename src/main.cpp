#include <SFML/Graphics.hpp>
#include <assert.h>

#include "maths/vectors.hpp"
#include "graphics/visual.hpp"
#include "gui/controls.hpp"

static const double DELTA_ANGLE = 1e-4;
static const size_t LENGTH = 1280;
static const size_t WIDTH  = 720;
static const double SCALE  = 0.05;

static const double AMBIENT = 0.2;

static const Vector2 NULL_VECTOR = {0, 0};

const char* DEFAULT_BUTTON = "assets/textures/button_default.png";
const char* PRESSED_BUTTON = "assets/textures/button_pressed.png";
const size_t BUTTON_LENGTH = 200;
const size_t BUTTON_WIDTH  = 80;

struct Scene
{
    Sphere& sphere;

    LightSource& light1;
    LightSource& light2;
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

    Vector3 light_pos   = {-5, 0, 10};
    Vector3 delta_light = {0, 1, 0};

    LightSource light  = {{-12, 15, 10}, {0.6, 0.9, 0.4}};
    LightSource light2 = {{15, 13, 11}, {0.8, 0, 0.8}};

    Sphere sphere = {system, 10, {0, 0}, WHITE, AMBIENT};

    Scene scene = {sphere, light, light2};

    Button up_but = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 100},
                     upper_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    Button low_but = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 300},
                     lower_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    Button right_but = {BUTTON_LENGTH, BUTTON_WIDTH, {300, 200},
                        righter_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    Button left_but = {BUTTON_LENGTH, BUTTON_WIDTH, {50, 200},
                       lefter_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    render_scene(scene);

    while (window.is_open())
    {
        window.closure_check();

        window.clear();

        window.draw_sphere(sphere);

        up_but.update_condition(window, &scene);
        low_but.update_condition(window, &scene);
        right_but.update_condition(window, &scene);
        left_but.update_condition(window, &scene);

        window.display();
    }

    return 0;
}

// ----------------------------------------------------------

void render_scene(Scene& scene)
{
    scene.sphere.clear();

    scene.sphere.add_light(scene.light1);
    scene.sphere.add_light(scene.light2);
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


