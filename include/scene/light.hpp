#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "maths/coord_system.hpp"
#include "graphics/pixels_array.hpp"

static const Vector3 RED   = {RGB_MAX,       0,       0};
static const Vector3 GREEN = {      0, RGB_MAX,       0};
static const Vector3 BLUE  = {      0,       0, RGB_MAX};
static const Vector3 BLACK = {      0,       0,       0};
static const Vector3 WHITE = {RGB_MAX, RGB_MAX, RGB_MAX};

namespace Scene
{

class LightSource
{
    public:

        LightSource(const Vector3& center, const Vector3& color);
        ~LightSource();

        Vector3 get_color_rgb()    const;
        Vector3 get_color_vector() const;
        Vector3 get_center()       const;

        void    set_center(const Vector3& center);
        void    set_color(const Vector3& color);

    private:

        Vector3 center_;
        Vector3 color_;
};

}

#endif // _LIGHT_HPP_
