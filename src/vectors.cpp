#include <cmath>
#include <stdio.h>
#include <assert.h>

#include "vectors.hpp"

static bool is_zero(const double num);

static const double EPSILON = 1e-9;

// ================================================================

// ----------------------------------------------------------------------

Vector2::Vector2(const double x, const double y)
{
    x_ = x;
    y_ = y;

    this->calculate_polar_system_();
}

// ----------------------------------------------------------------------

Vector2::~Vector2()
{
    x_ = NAN;
    y_ = NAN;

    angle_  = NAN;
    length_ = NAN;
}

// ----------------------------------------------------------------------

Vector2 Vector2::operator-() const
{
    return {-x_, -y_};
}

// ----------------------------------------------------------------------

Vector2 Vector2::operator+(const Vector2& second) const
{
    Vector2 result = *this;

    result.x_ += second.x_;
    result.y_ += second.y_;

    result.calculate_polar_system_();

    return result;
}

// ----------------------------------------------------------------------

Vector2 Vector2::operator-(const Vector2& second) const
{
    Vector2 result = *this;

    result.x_ -= second.x_;
    result.y_ -= second.y_;

    result.calculate_polar_system_();

    return result;
}

// ----------------------------------------------------------------------

Vector2 Vector2::operator*(const double scalar) const
{
    Vector2 result = *this;

    result.x_ *= scalar;
    result.y_ *= scalar;

    result.calculate_polar_system_();

    return result;
}

// ----------------------------------------------------------------------

Vector2 Vector2::operator/(const double scalar) const
{
    Vector2 result = *this;

    result.x_ /= scalar;
    result.y_ /= scalar;

    result.calculate_polar_system_();

    return result;
}

// ----------------------------------------------------------------------

Vector2 Vector2::operator=(const Vector2& second)
{
    this->x_ = second.x_;
    this->y_ = second.y_;

    return *this;
}

// ----------------------------------------------------------------------

void Vector2::print_vector() const
{
    Vector2 vec = *this;

    printf("%g %g\n", vec.x_, vec.y_);
}

// ----------------------------------------------------------------------

Vector2 Vector2::get_normal() const
{
    Vector2 res = {-y_, x_};

    return res;
}

// ----------------------------------------------------------------------

Vector2 Vector2::get_normalized() const
{
    assert(!is_zero(length_));

    Vector2 res = {x_ / length_, y_ / length_};

    return res;
}

// ----------------------------------------------------------------------

void Vector2::calculate_polar_system_()
{
    double angle = 0;

    if (is_zero(x_))
    {
        angle = M_PI;
    }
    else
        angle = atan(y_ / x_);

    double length = sqrt(x_ * x_ + y_ * y_);

    angle_ = angle;
    length_ = length;
}

// ----------------------------------------------------------------------

static bool is_zero(const double num)
{
    double diff = fabs(num);

    return (diff < EPSILON) ? true : false;
}

// ----------------------------------------------------------------------

void Vector2::calculate_rectangular_system_()
{
    x_ = length_ * cos(angle_);
    y_ = length_ * sin(angle_);
}

// ----------------------------------------------------------------------

void Vector2::rotate(const double delta_angle)
{
    angle_ += delta_angle;

    this->calculate_rectangular_system_();
}

// ----------------------------------------------------------------------

void Vector2::set_length(const double length)
{
    x_ = x_ * length / length_;
    y_ = y_ * length / length_;

    length_ = length;
}

// ----------------------------------------------------------------------

Vector3::Vector3(const double x, const double y, const double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

// ----------------------------------------------------------------------

Vector3::~Vector3()
{
    x_ = NAN;
    y_ = NAN;
    z_ = NAN;
}

// ----------------------------------------------------------------------

Vector3 Vector3::operator-() const
{
    return {-x_, -y_, -z_};
}

// ----------------------------------------------------------------------

Vector3 Vector3::operator+(const Vector3& second) const
{
    Vector3 result = *this;

    result.x_ += second.x_;
    result.y_ += second.y_;
    result.z_ += second.z_;

    return result;
}

// ----------------------------------------------------------------------

Vector3 Vector3::operator-(const Vector3& second) const
{
    Vector3 result = *this;

    result.x_ -= second.x_;
    result.y_ -= second.y_;
    result.z_ -= second.z_;

    return result;
}

// ----------------------------------------------------------------------

Vector3 Vector3::operator*(const double scalar) const
{
    Vector3 result = *this;

    result.x_ *= scalar;
    result.y_ *= scalar;
    result.z_ *= scalar;

    return result;
}

// ----------------------------------------------------------------------

Vector3 Vector3::operator/(const double scalar) const
{
    Vector3 result = *this;

    result.x_ /= scalar;
    result.y_ /= scalar;
    result.z_ /= scalar;

    return result;
}

// ----------------------------------------------------------------------

Vector3 Vector3::operator=(const Vector3& second)
{
    this->x_ = second.x_;
    this->y_ = second.y_;
    this->z_ = second.z_;

    return *this;
}

// ----------------------------------------------------------------------

void Vector3::print_vector() const
{
    Vector3 vec = *this;

    printf("%g %g %g\n", vec.x_, vec.y_, vec.z_);
}

