#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_

#include "coord_system.hpp"
#include "pixels_array.hpp"

struct LightSource
{
    Vector3        center;
    PixelCondition color;
};

class Sphere
{
    public:
        Sphere(RectangleSystem& system, const double radius, const Vector2& center, const PixelCondition& color);
        ~Sphere();

        Vector2         get_center() const { return center_; }
        double          get_radius() const { return radius_; }
        PixelCondition  get_color()  const { return color_; }
        RectangleSystem get_system() const { return system_; }

        u_int8_t* get_pixels_array() const;
        Vector3   get_surface_normal(const Dot& coords);

        void set_system(const RectangleSystem& system);

        bool belong_to_sphere(const Dot& coords);

        void add_light(const LightSource& light);

        void clear();

    private:
        double  radius_;
        Vector2 center_;
        Pixels  pixels_;
        RectangleSystem system_;
        PixelCondition  color_;

        void paint_sphere_point_(const Dot& pixel);
        void update_pixel_brightness_(const Dot& pixel, const LightSource& light);
};

double calculate_sphere_z(const Vector2& xy, const double radius);

#endif // _OBJECTS_HPP_
