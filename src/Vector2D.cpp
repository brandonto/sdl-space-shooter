/*******************************************************************//*
 * Implementation of the Vector2D class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-11
 * @modified    2014-09-14
 *********************************************************************/
#include "Vector2D.h"

#include <cmath>

Vector2D::Vector2D(float x, float y)
:   x(x), y(y)
{
}

Vector2D::~Vector2D()
{
}

void Vector2D::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Vector2D::magnitude()
{
    return sqrt(x*x + y*y);
}

void Vector2D::normalize()
{
    *this /= magnitude();
}

Vector2D Vector2D::getUnitVector()
{
    return Vector2D(x, y) / magnitude();
}

Vector2D Vector2D::operator+(const Vector2D &vector)
{
    return Vector2D(x + vector.x, y + vector.y);
}

Vector2D& Vector2D::operator+=(const Vector2D &vector)
{
    x += vector.x;
    y += vector.y;

    return *this;
}

Vector2D Vector2D::operator-(const Vector2D &vector)
{
    return Vector2D(x - vector.x, y - vector.y);
}

Vector2D& Vector2D::operator-=(const Vector2D &vector)
{
    x -= vector.x;
    y -= vector.y;

    return *this;
}

Vector2D Vector2D::operator*(float scalar)
{
    return Vector2D(x*scalar, y*scalar);
}

Vector2D& Vector2D::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

Vector2D Vector2D::operator/(float scalar)
{
    return Vector2D(x/scalar, y/scalar);
}

Vector2D& Vector2D::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}
