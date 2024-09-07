#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "coord_system.h"
#include "pixels_array.h"

class Sphere
{
    public:
        Sphere(RectangleSystem& system, const double radius, const Vector2 center);
        ~Sphere();

        void define_sphere();

        u_int8_t* get_pixels_array() const;

    private:
        double  radius_;
        Vector2 center_;
        Pixels  pixels_;
        RectangleSystem system_;

        void paint_sphere_point_(const Dot& pixel);
};

#endif // _OBJECTS_H_
