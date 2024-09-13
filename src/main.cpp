#include <SFML/Graphics.hpp>
#include <assert.h>

#include "maths/vectors.hpp"
#include "graphics/visual.hpp"
#include "gui/manager.hpp"

static const double DELTA_ANGLE = 1e-4;
static const size_t LENGTH = 1280;
static const size_t WIDTH  = 720;
static const double SCALE  = 0.05;

static const double AMBIENT = 0.2;

static const Vector2 NULL_VECTOR = {0, 0};

const char* DEFAULT_BUTTON = "assets/textures/button_default.png";
const char* PRESSED_BUTTON = "assets/textures/button_pressed.png";
const size_t BUTTON_LENGTH = 130;
const size_t BUTTON_WIDTH  = 50;

struct Objects
{
    Scene::Sphere& sphere;

    Scene::LightSource& light1;
    Scene::LightSource& light2;
};

void render_scene(Objects& scene);

void upper_light1(void* scene);
void lower_light1(void* scene);
void righter_light1(void* scene);
void lefter_light1(void* scene);

int main()
{
    RectangleSystem  system = {LENGTH, WIDTH, SCALE, {0, 0}};
    Graphics::Window window = {system, "Sphere"};

    Scene::LightSource light  = {{-12, 15, 10}, {153, 230, 100}};
    Scene::LightSource light2 = {{15, 13, 11}, {200, 0, 200}};

    Scene::Sphere sphere = {system, 6, {0, 0}, WHITE, AMBIENT};

    Objects scene = {sphere, light, light2};

    Manager manager = {};

    Button up_but = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 50}, ButtonType::HOLD,
                     upper_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    Button low_but = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 210}, ButtonType::HOLD,
                     lower_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    Button right_but = {BUTTON_LENGTH, BUTTON_WIDTH, {250, 130}, ButtonType::HOLD,
                        righter_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    Button left_but = {BUTTON_LENGTH, BUTTON_WIDTH, {100, 130}, ButtonType::HOLD,
                       lefter_light1, DEFAULT_BUTTON, PRESSED_BUTTON};

    manager.add_button(up_but);
    manager.add_button(low_but);
    manager.add_button(right_but);
    manager.add_button(left_but);

    render_scene(scene);

    while (window.is_open())
    {
        window.closure_check();

        window.clear();

        window.draw_sphere(sphere);

        manager.update(window, &scene);

        window.display();
    }

    return 0;
}

// ----------------------------------------------------------

void render_scene(Objects& scene)
{
    scene.sphere.clear();

    scene.sphere.add_light(scene.light1);
    scene.sphere.add_light(scene.light2);
}

// ----------------------------------------------------------

void upper_light1(void* scene_ptr)
{
    assert(scene_ptr);

    Objects* scene = (Objects*) scene_ptr;

    static const Vector3 UPPERLIGHT_DELTA = {0, 1, 0};
    scene->light1.set_center(scene->light1.get_center() + UPPERLIGHT_DELTA);

    render_scene(*scene);
}

// ----------------------------------------------------------

void lower_light1(void* scene_ptr)
{
    assert(scene_ptr);

    Objects* scene = (Objects*) scene_ptr;

    static const Vector3 LOWERLIGHT_DELTA = {0, -1, 0};
    scene->light1.set_center(scene->light1.get_center() + LOWERLIGHT_DELTA);

    render_scene(*scene);
}

// ----------------------------------------------------------

void righter_light1(void* scene_ptr)
{
    assert(scene_ptr);

    Objects* scene = (Objects*) scene_ptr;

    static const Vector3 RIGHTERLIGHT_DELTA = {1, 0, 0};
    scene->light1.set_center(scene->light1.get_center() + RIGHTERLIGHT_DELTA);

    render_scene(*scene);
}

// ----------------------------------------------------------

void lefter_light1(void* scene_ptr)
{
    assert(scene_ptr);

    Objects* scene = (Objects*) scene_ptr;

    static const Vector3 LEFTERLIGHT_DELTA = {-1, 0, 0};
    scene->light1.set_center(scene->light1.get_center() + LEFTERLIGHT_DELTA);

    render_scene(*scene);
}


