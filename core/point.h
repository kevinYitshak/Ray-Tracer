#ifndef CG1RAYTRACER_POINT_HEADER
#define CG1RAYTRACER_POINT_HEADER

#include <core/assert.h>
#include <core/macros.h>

namespace rt {

class Vector;
class Float4;

class ALIGN(16) Point {
public:
    float x, y, z;

    Point() = default;                       // constructor
    Point(float x, float y, float z);        // constructor with parameters
    explicit Point(const Float4& f4);

    static Point rep(float v) { return Point(v,v,v); } // rep value is shared for every obj instances

    Vector operator-(const Point& b) const;

    bool operator==(const Point& b) const;
    bool operator!=(const Point& b) const;

};

// creating objects for Point class

Point operator*(float scalar, const Point& b); // operator * (mul) overloading 
Point operator*(const Point& a, float scalar);
Point operator+(const Point& a, const Point& b);

Point min(const Point& a, const Point& b);
Point max(const Point& a, const Point& b);

}

#endif