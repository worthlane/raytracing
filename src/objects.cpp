#include <stdio.h>
#include <assert.h>
#include <cmath>

#include "objects.hpp"

static size_t get_pixel_position(const RectangleSystem& system, const Dot& pixel);

static PixelCondition calculate_point_brightness(Sphere& sphere, const Dot& coords, const LightSource& light);
static PixelCondition calculate_illumination(Sphere& sphere, const Vector3& falling_ray, const Vector3& surface_normal);
static PixelCondition calculate_glare(Sphere& sphere, const Vector3& falling_ray,
                                      const Vector3& surface_normal, const PixelCondition& color);

// =======================================================================

Sphere::Sphere(RectangleSystem& system, const double radius, const Vector2& center, const PixelCondition& color) :
    center_(center), system_(system), pixels_(system.get_length() * system.get_width() * 4)
{
    radius_ = radius;
    color_  = color;
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

void Sphere::paint_sphere_point_(const Dot& pixel)
{
    Dot    coords   = system_.pixel_to_coords(pixel);

    Vector2 sphere_distance = coords - center_;

    if (!(this->belong_to_sphere(coords)))
        return;

    double z = calculate_sphere_z(sphere_distance, radius_);
    double brightness = z / radius_;

    PixelCondition color = color_;
    color *= brightness;

    size_t position = get_pixel_position(system_, pixel);
    pixels_.paint_pixel(position, color);
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

    PixelCondition delta_color = calculate_illumination(sphere, falling_ray, surface_normal);
    delta_color += calculate_glare(sphere, falling_ray, surface_normal, light.color);

    return delta_color;
}

// ----------------------------------------------------------------------

static PixelCondition calculate_illumination(Sphere& sphere, const Vector3& falling_ray, const Vector3& surface_normal)
{
    double cos = cosinus(falling_ray, surface_normal);
    double brightness = (cos < 0) ? 0 : cos;

    PixelCondition illumination = sphere.get_color();
    illumination *= brightness;

    return illumination;
}

// ----------------------------------------------------------------------

static PixelCondition calculate_glare(Sphere& sphere, const Vector3& falling_ray,
                                      const Vector3& surface_normal, const PixelCondition& color)
{
    Vector3 reflected = reflect_vector(falling_ray, surface_normal);

    static const Vector3 CAMERA     = {0, 0, 1};
    static const int     GLARE_COEF = 25;

    double cos = cosinus(reflected, CAMERA);
    double brightness = (cos < 0) ? 0 : cos;

    PixelCondition glare = color;
    glare *= pow(brightness, GLARE_COEF);

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

