/*******************************************************************//*
 * Implementation of the Vector2D class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-11
 * @modified    2014-09-11
 *********************************************************************/
#include "Vector2D.h"

#include <SDL2/SDL.h>

Vector2D::Vector2D(float x, float y)
:   x(x), y(y)
{
}

Vector2D::~Vector2D();
{
}


Vector2D Vector2D::operator+(const Vector2D &vector1, const Vector2D &vector2)
{
    return Vector2D(vector1.x + vector2.x, vector1.y + vector2.y);
}

Vector2D Vector2D::operator-(const Vector2D &vector1, const Vector2D &vector2);
{
    return Vector2D(vector1.x - vector2.x, vector1.y - vector2.y);
}
