#ifndef _VECTORS_HPP_
#define _VECTORS_HPP_

#include <cmath>

class Vector2
{
    public:
        Vector2(const double x, const double y);
        ~Vector2();

        double get_x() const { return x_; }
        double get_y() const { return y_; }
        double get_angle()  const { return angle_; }
        double get_length() const { return length_; }

        void set_length(const double length);

        Vector2 operator-() const;
        Vector2 operator-(const Vector2& second) const; // TODO вынести
        Vector2 operator+(const Vector2& second) const;
        Vector2 operator*(const double scalar)  const;
        Vector2 operator/(const double scalar)  const;
        Vector2 operator=(const Vector2& second);

        void rotate(const double delta_angle);

        Vector2 get_normal()     const;
        Vector2 get_normalized() const;

        void print_vector() const;

    private:
        double x_, y_;
        double angle_, length_;

        void calculate_polar_system_();
        void calculate_rectangular_system_();
};

class Vector3
{
    public:
        Vector3(const double x, const double y, const double z);
        ~Vector3();

        double get_x() const { return x_; }
        double get_y() const { return y_; }
        double get_z() const { return z_; }

        Vector3 operator-() const;
        Vector3 operator-(const Vector3& second) const; // TODO вынести
        Vector3 operator+(const Vector3& second) const;
        Vector3 operator*(const double scalar)  const;
        Vector3 operator/(const double scalar)  const;

        Vector3 operator=(const Vector3& second);

        void print_vector() const;

    private:
        double x_, y_, z_;
};

typedef Vector2 Dot;

#endif // _VECTORS_HPP_
