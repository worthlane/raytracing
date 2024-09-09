#include "visual.hpp"

static const float DOT_RADIUS = 1.0;

static const Vector2 NULL_VECTOR = {0, 0};

// ==============================================================

Visual::Visual(const RectangleSystem& system, const char* name) :
    window_(sf::VideoMode(system.get_length(), system.get_width()), name),
    system_(system)
{
}

// ----------------------------------------------------------------------

Visual::~Visual()
{
    window_.close();
}

// ----------------------------------------------------------------------

bool Visual::is_open()
{
    return window_.isOpen();
}

// ----------------------------------------------------------------------

void Visual::clear()
{
    window_.clear();
}

// ----------------------------------------------------------------------

void Visual::display()
{
    window_.display();
}

// ----------------------------------------------------------------------

void Visual::close()
{
    window_.close();
}

// ----------------------------------------------------------------------

void Visual::closure_check()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

// ----------------------------------------------------------------------

Vector2 Visual::get_mouse_position() // TODO refactor
{
    sf::Vector2i vector = sf::Mouse::getPosition();

    double x = vector.x;
    double y = vector.y;

    static const size_t Y_SHIFT = 2334;
    static const size_t X_SHIFT = 1942;

    //printf("%lf %f\n", x, y);

    Vector2 pos = {x - X_SHIFT, y - Y_SHIFT};

    //pos.print_vector();

    Vector2 res = system_.coords_to_pixel(pos);

    res.print();

    return res; // res
}

// ----------------------------------------------------------------------

void Visual::draw_sphere(const Sphere& sphere)
{
    sf::Texture texture;
    texture.create(system_.get_length(), system_.get_width());
    sf::Sprite sprite;

    u_int8_t* pixels = sphere.get_pixels_array();

    texture.update(pixels);

    sprite.setTexture(texture);

    window_.draw(sprite);
}

