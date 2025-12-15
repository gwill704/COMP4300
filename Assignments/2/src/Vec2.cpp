#include "Vec2.h"
#include <math.h>

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{

}


bool Vec2::operator == (const Vec2 & rhs) const
{
    return (x == rhs.x) && (y == rhs.y);
}


bool Vec2::operator != (const Vec2 & rhs) const
{
    return (x != rhs.x) || (y != rhs.y);
}


Vec2 Vec2::operator + (const Vec2 & rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}


Vec2 Vec2::operator - (const Vec2 & rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}


Vec2 Vec2::operator * (float val) const
{
    return Vec2(x * val, y * val);
}


Vec2 Vec2::operator / (float val) const
{
    return Vec2(x / val, y / val);
}


void Vec2::operator += (const Vec2 & rhs)
{
    x += rhs.x;
    y += rhs.y;
}


void Vec2::operator -= (const Vec2 & rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}


void Vec2::operator *= (const float val)
{
    x *= val;
    y *= val;
}


void Vec2::operator /= (const float val)
{
    x /= val;
    y /= val;
}


Vec2 Vec2::dist(const Vec2 & rhs) const
{
    return (rhs - (*this));
}


float Vec2::length() const
{
    //return pow((this->x * this->x + this->y * this->y), .5); this one is a bit slower
    return sqrt(x*x + y*y);
}

Vec2 Vec2::normalize()
{
    *this /= this->length();
    return *this;
}