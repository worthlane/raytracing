#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

#include "maths/vectors.hpp"
#include "graphics/visual.hpp"
#include "gui/manager.hpp"
#include "gui/actions.hpp"

static const double DELTA_ANGLE = 1e-4;
static const size_t LENGTH = 1280;
static const size_t WIDTH  = 720;
static const double SCALE  = 0.05;

static const double AMBIENT = 0.2;

static const Vector2 NULL_VECTOR = {0, 0};

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

    LightMoveAction up    = {&light, &light2, { 0,  1, 0}};
    LightMoveAction down  = {&light, &light2, { 0, -1, 0}};
    LightMoveAction left  = {&light, &light2, {-1,  0, 0}};
    LightMoveAction right = {&light, &light2, { 1,  0, 0}};

    LightColorAction red_light  = {&light, &light2, RED};
    LightColorAction grn_light  = {&light, &light2, GREEN};
    LightColorAction cst_light  = {&light, &light2, {153, 230, 100}};
    LightColorAction blu_light  = {&light, &light2, BLUE};
    LightColorAction cst2_light = {&light, &light2, {200, 0, 200}};

    Manager manager = {};

    SubscribeButton up_but    = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 50}, &up};
    SubscribeButton low_but   = {BUTTON_LENGTH, BUTTON_WIDTH, {180, 210}, &down};
    SubscribeButton right_but = {BUTTON_LENGTH, BUTTON_WIDTH, {250, 130}, &right};
    SubscribeButton left_but = {BUTTON_LENGTH, BUTTON_WIDTH, {100, 130}, &left};

    AnimatedButton red = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 200}, &red_light, RED};
    AnimatedButton grn = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 250}, &grn_light, GREEN};
    AnimatedButton cst = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 300}, &cst_light, {153, 230, 100}};
    AnimatedButton blu = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 350}, &blu_light, BLUE};
    AnimatedButton cst2 = {BUTTON_LENGTH, BUTTON_WIDTH, {1000, 400}, &cst2_light, {200, 0, 200}};

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

        Graphics::Event event;
        window.poll_event(event);

        window.clear();

        bool flag = manager.update(window, event);

        if (flag)
            render_scene(scene);

        window.draw_sphere(sphere);
        window.draw_light(light);
        window.draw_light(light2);

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
