#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_

#include "coord_system.hpp"
#include "pixels_array.hpp"

struct LightSource
{
    Vector3 center;
};

class Sphere
{
    public:
        Sphere(RectangleSystem& system, const double radius, const Vector2& center, const PixelCondition& color);
        ~Sphere();

        void render_sphere();

        Vector3 get_surface_normal(const Dot& coords);

        bool belong_to_sphere(const Dot& coords);

        u_int8_t* get_pixels_array() const;

    private:
        double  radius_;
        Vector2 center_;
        Pixels  pixels_;
        RectangleSystem system_;
        PixelCondition color_;

        void paint_sphere_point_(const Dot& pixel);
        void lighten_sphere_point_(const Dot& pixel, const double brightness);
};

double calculate_sphere_z(const Vector2& xy, const double radius);

#endif // _OBJECTS_HPP_
