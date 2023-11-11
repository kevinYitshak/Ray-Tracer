#include <core/point.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

    Point::Point(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point::Point(const Float4& f4)
    {
        assert(f4.w!=0);
    this->x=f4.x/f4.w;
    this->y=f4.y/f4.w;
    this->z=f4.z/f4.w;
    }

    Vector Point::operator - (const Point& b) const {
        return Vector(x - b.x, y - b.y, z - b.z);
    }

    bool Point::operator == (const Point& b) const {

        return ((x == b.x) && (y == b.y) && (z == b.z));
    }

    bool Point::operator != (const Point& b) const {

        return ((x != b.x) && (y != b.y) && (z != b.z));
    }

    Point operator*(float scalar, const Point& b)
    {
        return Point(scalar * b.x, scalar * b.y, scalar * b.z);
    }

    Point operator*(const Point& a, float scalar)
    {
        return Point(a.x * scalar, a.y * scalar, a.z * scalar);
    }

    Point operator + (const Point& a, const Point& b) 
    {
        return Point(a.x + b.x, a.y + b.y, a.z + b.z);
    }


    Point min(const Point& a, const Point& b)
    {   
        Point new_min;

        new_min.x = std::min(a.x, b.x);
        new_min.y = std::min(a.y, b.y);
        new_min.z = std::min(a.z, b.z);

        return new_min;
    }

    Point max(const Point& a, const Point& b)
    {   
        Point new_max;
        
        new_max.x = std::max(a.x, b.x);
        new_max.y = std::max(a.y, b.y);
        new_max.z = std::max(a.z, b.z);
        
        return new_max;
    }

}

