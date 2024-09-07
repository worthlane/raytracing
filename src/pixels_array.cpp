#include <assert.h>
#include <stdio.h>

#include "pixels_array.h"

Pixels::Pixels(const size_t size)
{
    u_int8_t* pixels = new u_int8_t[size];

    pixels_ = pixels;
    size_   = size;
}

Pixels::~Pixels()
{
    delete[] pixels_;

    size_   = NAN;
}

void Pixels::paint_pixel(const size_t position,
                         const u_int8_t red, const u_int8_t green, const u_int8_t blue)
{
    assert(position + 3 < size_);

    pixels_[position]     = red;
    pixels_[position + 1] = green;
    pixels_[position + 2] = blue;
    pixels_[position + 3] = NOT_TRANSPARENT;
}

u_int8_t* Pixels::get_array() const
{
    return pixels_;
}


