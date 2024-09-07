#ifndef _PIXELS_ARRAY_H_
#define _PIXELS_ARRAY_H_

#include <cmath>

static const u_int8_t RGB_MAX         = 255;
static const u_int8_t NOT_TRANSPARENT = 255;

class Pixels
{
    public:
        Pixels(const size_t size);
        ~Pixels();

        u_int8_t* get_array() const;

        void paint_pixel(const size_t position,
                         const u_int8_t red, const u_int8_t green, const u_int8_t blue);

    private:
        size_t    size_;
        u_int8_t* pixels_;
};

#endif // _PIXELS_ARRAY_H_
