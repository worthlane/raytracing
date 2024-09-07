#include <stdio.h>

#include "coord_system.h"

static const size_t X_CENTER_STD = 240;
static const size_t Y_CENTER_STD = 320;

static const double DX = 1;
static const double DY = 1;

RectangleSystem::RectangleSystem(const size_t length, const size_t width, const double scale) :
    center_(length / 2, width / 2)
{
    scale_ = scale;

    length_ = length;
    width_  = width;
}

RectangleSystem::~RectangleSystem()
{
    scale_ = NAN;

    width_  = NAN;
    length_ = NAN;
}

size_t RectangleSystem::get_width() const
{
    return width_;
}

size_t RectangleSystem::get_length() const
{
    return length_;
}

Vector2 RectangleSystem::coords_to_pixel(const Vector2& vec)
{
    double x = vec.get_x();
    double y = vec.get_y();

    size_t x_center = center_.get_x();
    size_t y_center = center_.get_y();

    double x_pixel = x_center + x * DX / scale_;
    double y_pixel = y_center - y * DY / scale_;

    Vector2 result = {x_pixel, y_pixel};

    return result;
}

Vector2 RectangleSystem::pixel_to_coords(const Vector2& pixel)
{
    double x_pixel = pixel.get_x();
    double y_pixel = pixel.get_y();

    double x_center = center_.get_x();
    double y_center = center_.get_x();

    double x = (x_pixel - x_center) * scale_ / DX;
    double y = (y_pixel - y_center) * scale_ / DY;

    Vector2 result = {x, y};

    return result;
}

double RectangleSystem::get_scale() const
{
    return scale_;
}

