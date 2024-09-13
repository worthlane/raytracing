#include "scene/light.hpp"

Scene::LightSource::LightSource(const Vector3& center, const Vector3& color) :
    center_(center), color_(color)
{
    center_ = center;
    color_  = color / RGB_MAX;
}

// ------------------------------------------

Scene::LightSource::~LightSource()
{
}

// ------------------------------------------

Vector3 Scene::LightSource::get_color_rgb() const
{
    Vector3 color = {(size_t) (color_.get_x() * RGB_MAX),
                     (size_t) (color_.get_y() * RGB_MAX),
                     (size_t) (color_.get_z() * RGB_MAX)};

    return color;
}

// ------------------------------------------

Vector3 Scene::LightSource::get_color_vector() const
{
    return color_;
}

// ------------------------------------------

Vector3 Scene::LightSource::get_center() const
{
    return center_;
}

// ------------------------------------------

void Scene::LightSource::set_center(const Vector3& center)
{
    center_ = center;
}

// ------------------------------------------

void Scene::LightSource::set_color(const Vector3& color)
{
    color_ = color / RGB_MAX;
}
