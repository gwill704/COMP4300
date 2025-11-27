#include "Vec2.h"
#include <math.h>

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{

}

    bool operator == (const Vec2 & rhs) const
    {
        return (x == x.rhs) && (y == y.rhs);
    }
    bool operator != (const Vec2 & rhs) const;

    Vec2 Vec2::operator + (const Vec2 & rhs) const
    {
        // TODO 
        return Vec2(0,0);
    }


    Vec2 operator - (const Vec2 & rhs) const;
    Vec2 operator * (float val) const;
    Vec2 operator / (float val) const;

    void operator += (const Vec2 & rhs);
    void operator -= (const Vec2 & rhs);
    void operator *= (const float val);
    void operator /= (const float val);

    float dist(const Vec2 & rhs) const;
    float length() const;
}