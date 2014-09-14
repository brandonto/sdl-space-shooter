/*******************************************************************//*
 * This class models the mathematical concept of a vector in two
 * dimensions. Supports adding, subtracting, multiplying, and dividing
 * operations through overload.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-11
 * @modified    2014-09-14
 *********************************************************************/
#ifndef SPACESHOOTER_VECTOR2D_H_
    #define SPACESHOOTER_VECTOR2D_H_

class Vector2D
{
    private:
        //Fields

    public:
        //Fields
        float x, y;

        //Constructor
        Vector2D(float x, float y);

        //Destructor
        ~Vector2D();

        //Methods
        void set(float x, float y);
        float magnitude();
        void normalize();
        Vector2D getUnitVector();

        //Overloaded operators
        Vector2D operator+(const Vector2D &vector);
        Vector2D& operator+=(const Vector2D &vector);
        Vector2D operator-(const Vector2D &vector);
        Vector2D& operator-=(const Vector2D &vector);
        Vector2D operator*(float scalar);
        Vector2D& operator*=(float scalar);
        Vector2D operator/(float scalar);
        Vector2D& operator/=(float scalar);
};


#endif

