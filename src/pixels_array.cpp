#include <assert.h>
#include <stdio.h>

#include "pixels_array.hpp"

Pixels::Pixels(const size_t size)
{
    u_int8_t* pixels = new u_int8_t[size];

    pixels_ = pixels;
    size_   = size;
}

// ----------------------------------------------------------------------

Pixels::~Pixels()
{
    delete[] pixels_;

    size_   = NAN;
}

// ----------------------------------------------------------------------

void Pixels::paint_pixel(const size_t position, const PixelCondition& color)
{
    assert(position + 3 < size_);

    pixels_[position]     = color.red;
    pixels_[position + 1] = color.green;
    pixels_[position + 2] = color.blue;
    pixels_[position + 3] = color.transparency;
}

// ----------------------------------------------------------------------

u_int8_t* Pixels::get_array() const
{
    return pixels_;
}

// ----------------------------------------------------------------------

PixelCondition Pixels::get_pixel_color(const size_t position) const
{
    assert((position + 3 < size_) && (position % 4) == 0 &&
           "position should point at the start of pixel info in array");

    return {pixels_[position], pixels_[position + 1], pixels_[position + 2], pixels_[position + 3]};
}

// ----------------------------------------------------------------------

void Pixels::lighten_pixel(const size_t position, const double brightness)
{
    assert((position + 3 < size_) && (position % 4) == 0 &&
           "position should point at the start of pixel info in array");
    assert(brightness >= 0 && brightness <= 1 && "brightness coefficient should be in [0, 1] range");

    PixelCondition color = this->get_pixel_color(position);

    color *= brightness;

    this->paint_pixel(position, color);
}

// ----------------------------------------------------------------------

PixelCondition operator*=(PixelCondition& self, const double coef)
{
    self.red   *= coef;
    self.green *= coef;
    self.blue  *= coef;

    return self;
}

// ----------------------------------------------------------------------

PixelCondition operator+=(PixelCondition& self, const PixelCondition& second)
{
    int red   = self.red          + second.red;
    int green = self.green        + second.green;
    int blue  = self.blue         + second.blue;
    int trans = self.transparency + second.transparency;


    self.red          = (red   >= RGB_MAX) ? RGB_MAX : red;
    self.green        = (green >= RGB_MAX) ? RGB_MAX : green;
    self.blue         = (blue  >= RGB_MAX) ? RGB_MAX : blue;
    self.transparency = (trans >= RGB_MAX) ? RGB_MAX : trans;

    return self;
}


