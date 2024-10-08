#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_

#include "maths/coord_system.hpp"
#include "graphics/pixels_array.hpp"
#include "scene/light.hpp"

namespace Scene
{

class Sphere
{
    public:
        Sphere(RectangleSystem& system, const double radius, const Vector2& center, const Vector3& color, const double ambient);
        ~Sphere();

        Vector2         get_center()  const { return center_; }
        double          get_radius()  const { return radius_; }
        Vector3         get_color()   const { return color_; }
        RectangleSystem get_system()  const { return system_; }
        double          get_ambient() const { return ambient_; }

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
        Vector3 color_;
        double  ambient_;

        void update_pixel_brightness_(const Dot& pixel, const LightSource& light);
};

}

double calculate_sphere_z(const Vector2& xy, const double radius);

#endif // _OBJECTS_HPP_
