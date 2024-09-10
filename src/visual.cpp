#include "visual.hpp"

static const float DOT_RADIUS = 1.0;

static const Vector2 NULL_VECTOR = {0, 0};

// ==============================================================

Window::Window(const RectangleSystem& system, const char* name) :
    window_(sf::VideoMode(system.get_length(), system.get_width()), name),
    system_(system)
{
}

// ----------------------------------------------------------------------

Window::~Window()
{
    window_.close();
}

// ----------------------------------------------------------------------

bool Window::is_open()
{
    return window_.isOpen();
}

// ----------------------------------------------------------------------

void Window::clear()
{
    window_.clear();
}

// ----------------------------------------------------------------------

void Window::display()
{
    window_.display();
}

// ----------------------------------------------------------------------

void Window::close()
{
    window_.close();
}

// ----------------------------------------------------------------------

void Window::closure_check()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

// ----------------------------------------------------------------------

void Window::draw_sphere(const Sphere& sphere)
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

void Window::set_system(const RectangleSystem& system)
{
    system_ = system;
}
