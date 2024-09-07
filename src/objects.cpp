#include <stdio.h>

#include "objects.h"

Sphere::Sphere(RectangleSystem& system, const double radius, const Vector2 center) :
    center_(center), system_(system), pixels_(system.get_length() * system.get_width() * 4)
{
    radius_ = radius;
}

Sphere::~Sphere()
{
    radius_ = NAN;
}

void Sphere::define_sphere()
{
    size_t length = system_.get_length();
    size_t width  = system_.get_width();

    for (size_t y_pixel = 0; y_pixel < width; y_pixel++)
    {
        for (size_t x_pixel = 0; x_pixel < length; x_pixel++)
        {
            Dot pixel  = {x_pixel, y_pixel};

            size_t position = (y_pixel * length + x_pixel) * 4;

            /*pixels_.get_array()[position]     = 255;
            pixels_.get_array()[position + 1] = 0;
            pixels_.get_array()[position + 2] = 0;
            pixels_.get_array()[position + 3] = 255;*/

            //pixels_.paint_pixel(position, 255, 0, 0);

            this->paint_sphere_point_(pixel);
        }
    }
}

void Sphere::paint_sphere_point_(const Dot& pixel)
{
    Dot coords = system_.pixel_to_coords(pixel);

    size_t x_pixel = pixel.get_x();
    size_t y_pixel = pixel.get_y();
    size_t length  = system_.get_length();

    size_t position = (y_pixel * length + x_pixel) * 4;

    Vector2 sphere_distance = coords - center_;

    if (sphere_distance.get_length() < radius_)
        pixels_.paint_pixel(position, RGB_MAX, 0, 0);
    else
        pixels_.paint_pixel(position, 0, 0, RGB_MAX);


}

u_int8_t* Sphere::get_pixels_array() const
{
    return pixels_.get_array();
}

