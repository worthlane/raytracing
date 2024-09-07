#include "visual.h"

static const float DOT_RADIUS = 1.0;

static const Vector2 NULL_VECTOR = {0, 0};

// ==============================================================

Visual::Visual(const RectangleSystem& system, const char* name) :
    window_(sf::VideoMode(system.get_length(), system.get_width()), name),
    system_(system)
{
}

Visual::~Visual()
{
    window_.close();
}

bool Visual::is_open()
{
    return window_.isOpen();
}

void Visual::clear()
{
    window_.clear();
}

void Visual::display()
{
    window_.display();
}

void Visual::close()
{
    window_.close();
}

void Visual::closure_check()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

void Visual::draw_line(const Dot& start_dot, const Dot& end_dot, const sf::Color color)
{
    Dot new_start_dot = system_.coords_to_pixel(start_dot);
    Dot   new_end_dot = system_.coords_to_pixel(end_dot);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(new_start_dot.get_x(), new_start_dot.get_y())),
        sf::Vertex(sf::Vector2f(new_end_dot.get_x(),   new_end_dot.get_y()))
    };

    line[0].color  = color;
    line[1].color  = color;

    window_.draw(line, 2, sf::Lines);
}

void Visual::draw_dot(const Dot& dot, const sf::Color color)
{
    Dot dot_pixel = system_.coords_to_pixel(dot);

    sf::CircleShape shape;
    shape.setRadius(DOT_RADIUS);
    shape.setPosition(dot_pixel.get_x(), dot_pixel.get_y());
    shape.setFillColor(color);

    window_.draw(shape);
}

void Visual::draw_free_vector(const Dot& end_point, const sf::Color color)
{
    this->draw_vector(NULL_VECTOR, end_point, color);
}

void Visual::draw_vector(const Dot& start_point, const Vector2& vector, const sf::Color color)
{
    Dot end_point = start_point + vector;

    Vector2 normalized_vector = vector.get_normalized();
    Vector2 normalized_normal = (vector.get_normal()).get_normalized();

    const double ARROW_SCALE = 10 * system_.get_scale();

    normalized_vector.set_length(ARROW_SCALE);
    normalized_normal.set_length(ARROW_SCALE);

    Dot left_arrow_part  = end_point + normalized_normal - normalized_vector;
    Dot right_arrow_part = end_point - normalized_normal - normalized_vector;

    this->draw_line(start_point, end_point, color);
    this->draw_line(end_point, left_arrow_part, color);
    this->draw_line(end_point, right_arrow_part, color);
}

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

    res.print_vector();

    return res; // res
}

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

