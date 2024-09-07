#ifndef _COORD_SYSTEM_H_
#define _COORD_SYSTEM_H_

#include "vectors.h"

class RectangleSystem
{
    public:
        RectangleSystem(const size_t length, const size_t width, const double scale);
        ~RectangleSystem();

        size_t get_width()  const;
        size_t get_length() const;
        double get_scale()  const;

        Vector2 coords_to_pixel(const Vector2& vec);

        Vector2 pixel_to_coords(const Vector2& pixel);

    private:
        double scale_;
        Dot    center_;
        size_t width_, length_;
};

#endif // _COORD_SYSTEM_H
