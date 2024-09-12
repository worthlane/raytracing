#include <stdio.h>
#include <assert.h>
#include <cmath>

#include "scene/objects.hpp"

static size_t get_pixel_position(const RectangleSystem& system, const Dot& pixel);

static PixelCondition calculate_point_brightness(Sphere& sphere, const Dot& coords, const LightSource& light);
static Vector3 calculate_illumination(Sphere& sphere, const Vector3& falling_ray, const Vector3& surface_normal, const LightSource& light);
static Vector3 calculate_glare(Sphere& sphere, const Vector3& falling_ray,
                                      const Vector3& surface_normal, const LightSource& light);

// =======================================================================

Sphere::Sphere(RectangleSystem& system, const double radius, const Vector2& center, const Vector3& color, const double ambient) :
    center_(center), system_(system), pixels_(system.get_length() * system.get_width() * 4), color_(color)
{
    radius_  = radius;
    ambient_ = ambient;

}

// ----------------------------------------------------------------------

Sphere::~Sphere()
{
    radius_ = NAN;
}

// ----------------------------------------------------------------------

void Sphere::add_light(const LightSource& light)
{
    size_t length = system_.get_length();
    size_t width  = system_.get_width();

    for (size_t y_pixel = 0; y_pixel < width; y_pixel++)
    {
        for (size_t x_pixel = 0; x_pixel < length; x_pixel++)
        {
            Dot pixel  = {x_pixel, y_pixel};

            this->update_pixel_brightness_(pixel, light);
        }
    }
}

// ----------------------------------------------------------------------

void Sphere::update_pixel_brightness_(const Dot& pixel, const LightSource& light)
{
    Dot coords = system_.pixel_to_coords(pixel);

    if (!(this->belong_to_sphere(coords)))
        return;

    PixelCondition delta_color = calculate_point_brightness(*this, coords, light);

    size_t position = get_pixel_position(system_, pixel);

    PixelCondition color = pixels_.get_pixel_color(position);
    color += delta_color;

    pixels_.paint_pixel(position, color);
}

// ----------------------------------------------------------------------

static PixelCondition calculate_point_brightness(Sphere& sphere, const Dot& coords, const LightSource& light)
{
    Dot sphere_offset = coords - sphere.get_center();
    double z = calculate_sphere_z(sphere_offset, sphere.get_radius());

    Vector3 sphere_point = {coords.get_x(), coords.get_y(), z};
    Vector3 surface_normal = sphere.get_surface_normal(coords);
    Vector3 falling_ray = light.center - sphere_point;

    Vector3 delta_color = calculate_illumination(sphere, falling_ray, surface_normal, light);
    delta_color = delta_color + calculate_glare(sphere, falling_ray, surface_normal, light);

    delta_color %= 1;

    PixelCondition pixel = {delta_color.get_x() * RGB_MAX,
                            delta_color.get_y() * RGB_MAX,
                            delta_color.get_z() * RGB_MAX,
                            NOT_TRANSPARENT};



    return pixel;
}

// ----------------------------------------------------------------------

static Vector3 calculate_illumination(Sphere& sphere, const Vector3& falling_ray, const Vector3& surface_normal, const LightSource& light)
{
    double cos = cosinus(falling_ray, surface_normal);
    double diffusion = (cos < 0) ? 0 : cos;

    Vector3 material = sphere.get_color();
    Vector3 result = (material * light.color) * (diffusion + sphere.get_ambient());

    return result;
}

// ----------------------------------------------------------------------

static Vector3 calculate_glare(Sphere& sphere, const Vector3& falling_ray,
                                      const Vector3& surface_normal, const LightSource& light)
{
    Vector3 reflected = reflect_vector(falling_ray, surface_normal);

    static const Vector3 CAMERA     = {0, 0, 1};
    static const int     GLARE_COEF = 25;

    double cos = cosinus(reflected, CAMERA);
    double S = (cos < 0) ? 0 : cos;

    Vector3 glare = light.color;
    glare = glare * pow(S, GLARE_COEF);

    return glare;
}

// ----------------------------------------------------------------------

u_int8_t* Sphere::get_pixels_array() const
{
    return pixels_.get_array();
}

// ----------------------------------------------------------------------

static size_t get_pixel_position(const RectangleSystem& system, const Dot& pixel)
{
    size_t x_pixel = pixel.get_x();
    size_t y_pixel = pixel.get_y();
    size_t length  = system.get_length();

    size_t position = (y_pixel * length + x_pixel) * 4;

    return position;
}

// ----------------------------------------------------------------------

double calculate_sphere_z(const Vector2& xy, const double radius)
{
    double component2 = xy.get_length();

    double z2 = radius * radius - component2 * component2;

    assert(z2 >= 0);

    return sqrt(z2);
}

// ----------------------------------------------------------------------

Vector3 Sphere::get_surface_normal(const Dot& coords)
{
    Vector3 result = {0, 0, 0};

    if (!(this->belong_to_sphere(coords)))
        return result;

    Vector2 delta = coords - center_;
    double z = calculate_sphere_z(delta, radius_);

    result = {delta.get_x(), delta.get_y(), z};

    return result;
}

// ----------------------------------------------------------------------

bool Sphere::belong_to_sphere(const Dot& coords)
{
    Vector2 sphere_distance = coords - center_;

    return (sphere_distance.get_length() > radius_) ? false : true;
}

// ----------------------------------------------------------------------

void Sphere::set_system(const RectangleSystem& system)
{
    system_ = system;
    pixels_.clear();
}

// ----------------------------------------------------------------------

void Sphere::clear()
{
    pixels_.clear();
}

