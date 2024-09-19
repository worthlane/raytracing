#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

#include "maths/vectors.hpp"
#include "graphics/visual.hpp"
#include "gui/manager.hpp"
#include "gui/light_buttons.hpp"

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

int main()
{
    RectangleSystem  system = {LENGTH, WIDTH, SCALE, {0, 0}};
    Graphics::Window window = {system, "Sphere"};

    Scene::LightSource light  = {{-12, 15, 10}, {153, 230, 100}};
    Scene::LightSource light2 = {{15, 13, 11}, {200, 0, 200}};

    Scene::Sphere sphere = {system, 6, {0, 0}, WHITE, AMBIENT};

    Objects scene = {sphere, light, light2};

    Manager manager = {};

    MoveLightButton up_but = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 50},
                              &light, &light2, {0, 1, 0},
                              DEFAULT_BUTTON, PRESSED_BUTTON};

    MoveLightButton low_but = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 210},
                              &light, &light2, {0, -1, 0},
                              DEFAULT_BUTTON, PRESSED_BUTTON};

    MoveLightButton right_but = {BUTTON_LENGTH, BUTTON_WIDTH, {250, 130},
                                &light, &light2, {1, 0, 0},
                                DEFAULT_BUTTON, PRESSED_BUTTON};

    MoveLightButton left_but = {BUTTON_LENGTH, BUTTON_WIDTH, {100, 130},
                                &light, &light2, {-1, 0, 0},
                                DEFAULT_BUTTON, PRESSED_BUTTON};

    ColorLightButton red = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 200},
                            &light, &light2, RED};
    ColorLightButton grn = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 250},
                            &light, &light2, GREEN};
    ColorLightButton cst = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 300},
                            &light, &light2, {153, 230, 100}};
    ColorLightButton blu = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 350},
                            &light, &light2, BLUE};
    ColorLightButton cst2 = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 400},
                            &light, &light2, {200, 0, 200}};

    manager.add_button(&up_but);
    manager.add_button(&low_but);
    manager.add_button(&right_but);
    manager.add_button(&left_but);
    manager.add_button(&red);
    manager.add_button(&grn);
    manager.add_button(&blu);
    manager.add_button(&cst);
    manager.add_button(&cst2);

    render_scene(scene);

    while (window.is_open())
    {
        window.closure_check();

        window.clear();

        bool flag = manager.update(window);

        if (flag)
            render_scene(scene);

        window.draw_sphere(sphere);

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
