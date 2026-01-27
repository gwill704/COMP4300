#include <math.h>

class Vec2f
{
public:
    float x, y;

    Vec2f() = default;

    Vec2f(float xin, float yin)
        : x(xin), y(yin)
    {

    }

    Vec2f(float angle)
        : x(cosf(angle)), y(sinf(angle))
    {

    }


    bool operator == (const Vec2f & rhs) const
    {
        return (x == rhs.x) && (y == rhs.y);
    }


    bool operator != (const Vec2f & rhs) const
    {
        return (x != rhs.x) || (y != rhs.y);
    }


    Vec2f operator + (const Vec2f & rhs) const
    {
        return Vec2f(x + rhs.x, y + rhs.y);
    }


    Vec2f operator - (const Vec2f & rhs) const
    {
        return Vec2f(x - rhs.x, y - rhs.y);
    }


    Vec2f operator * (float val) const
    {
        return Vec2f(x * val, y * val);
    }


    Vec2f operator / (float val) const
    {
        return Vec2f(x / val, y / val);
    }


    void operator += (const Vec2f & rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }


    void operator -= (const Vec2f & rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
    }


    void operator *= (const float val)
    {
        x *= val;
        y *= val;
    }


    void operator /= (const float val)
    {
        x /= val;
        y /= val;
    }


    Vec2f dist(const Vec2f & rhs) const
    {
        return (rhs - (*this));
    }


    float length() const
    {
        //return pow((this->x * this->x + this->y * this->y), .5); this one is a bit slower
        return sqrt( x*x + y*y );
    }

    float length2() const
    {
        return ( x*x + y*y );
    }


    Vec2f normalize()
    {
        if (this->length() == 0) return *this;
        *this /= this->length();
        return *this;
    }

    float getAngle()
    {
        return atan2f(-y, x);
    }
};
