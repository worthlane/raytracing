#include "graphics/visual.hpp"

static const float DOT_RADIUS = 1.0;

static const Vector2 NULL_VECTOR = {0, 0};

// ==============================================================

Graphics::Window::Window(const RectangleSystem& system, const char* name) :
    window_(sf::VideoMode(system.get_length(), system.get_width()), name),
    system_(system)
{
}

// ----------------------------------------------------------------------

Graphics::Window::~Window()
{
    window_.close();
}

// ----------------------------------------------------------------------

bool Graphics::Window::is_open()
{
    return window_.isOpen();
}

// ----------------------------------------------------------------------

void Graphics::Window::clear()
{
    window_.clear();
}

// ----------------------------------------------------------------------

void Graphics::Window::display()
{
    window_.display();
}

// ----------------------------------------------------------------------

void Graphics::Window::close()
{
    window_.close();
}

// ----------------------------------------------------------------------

void Graphics::Window::closure_check()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

// ----------------------------------------------------------------------

void Graphics::Window::draw_sphere(const Scene::Sphere& sphere)
{
    sf::Texture texture;
    texture.create(system_.get_length(), system_.get_width());
    sf::Sprite sprite;

    u_int8_t* pixels = sphere.get_pixels_array();

    texture.update(pixels);

    sprite.setTexture(texture);

    window_.draw(sprite);
}

// ----------------------------------------------------------------------

void Graphics::Window::draw(const Graphics::Sprite& sprite) // TODO convert
{
    window_.draw(sprite.get_sprite());
}

// ----------------------------------------------------------------------

void Graphics::Window::set_system(const RectangleSystem& system)
{
    system_ = system;
}

// ------------------------------------------

void Graphics::Window::draw_light(const Scene::LightSource& light)
{
    static const double LIGHT_RADIUS = 5;

    sf::CircleShape shape;

    Vector3 center = light.get_center();
    Dot center_coords = {center.get_x(), center.get_y()};

    Dot center_pixel = system_.coords_to_pixel(center_coords);
    Vector3 light_color = light.get_color_rgb();

    sf::Color col = {light_color.get_x(), light_color.get_y(), light_color.get_z()};

    shape.setRadius(LIGHT_RADIUS);
    shape.setPosition(center_pixel.get_x(), center_pixel.get_y());
    shape.setFillColor(col);

    window_.draw(shape);
}

// ------------------------------------------

bool Graphics::Window::poll_event(Event& event)
{
    return window_.pollEvent(event.get_event());
}
