#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>

namespace rt {

    Vector::Vector(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector::Vector(const Float4& f4)
    {
        assert(f4.w == 0);
        this->x = f4.x;
        this->y = f4.y;
        this->z = f4.z;
    }

    Vector Vector::operator + (const Vector& b) const {
        /* TODO */
        Vector add;
        add.x = this->x + b.x;
        add.y = this->y + b.y;
        add.z = this->z + b.z;
        return add;
    }

    Vector Vector::operator - (const Vector& b) const {
        Vector minus;
        minus.x = this->x - b.x;
        minus.y = this->y - b.y;
        minus.z = this->z - b.z;
        return minus;
    }

    Vector Vector::operator - () const {
        Vector minus;
        minus.x = -1 * this->x;
        minus.y = -1 * this->y;
        minus.z = -1 * this->z;
        return minus;
    }

    Vector Vector::normalize() const {
        Vector norm;
        float length = this->length();
        norm.x = this->x / length;
        norm.y = this->y / length;
        norm.z = this->z / length;
        return norm;
    }

    Vector operator * (float scalar, const Vector& b) {
        Vector scaled;
        scaled.x = scalar * (b.x);
        scaled.y = scalar * (b.y);
        scaled.z = scalar * (b.z);
        return scaled;

    }

    Vector operator * (const Vector& a, float scalar) {
        Vector scaled;
        scaled.x = a.x * scalar;
        scaled.y = a.y * scalar;
        scaled.z = a.z * scalar;
        return scaled;
    }

    Vector operator / (const Vector& a, float scalar) {
        Vector divided;
        divided.x = (a.x) / scalar;
        divided.y = (a.y) / scalar;
        divided.z = (a.z) / scalar;
        return divided;
    }

    Vector cross(const Vector& a, const Vector& b) {
        Vector cross;
        cross.x = (a.y) * (b.z) - (a.z) * (b.y);
        cross.y = -1 * ((a.x) * (b.z) - (a.z) * (b.x));
        cross.z = (a.x) * (b.y) - (a.y) * (b.x);
        return cross;


    }

    float dot(const Vector& a, const Vector& b) {
        float dot;
        dot = a.x * b.x + a.y * b.y + a.z * b.z;
        return dot;
    }

    float Vector::lensqr() const {
        float square;
        square = powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2);
        return square; 
    }

    float Vector::length() const {
        return sqrt(this->lensqr());
    }

    bool Vector::operator == (const Vector& b) const {
        if ((this->x == b.x) && (this->y == b.y) && (this->z == b.z))
        {
            return true;
        }
        return false;
    }

    bool Vector::operator != (const Vector& b) const {
        if ((this->x == b.x) && (this->y == b.y) && (this->z == b.z))
        {
            return false;
        }
        return true;
    }

    Vector min(const Vector& a, const Vector& b) {
        Vector min;
        min.x = std::min(a.x, b.x);
        min.y = std::min(a.y, b.y);
        min.z = std::min(a.z, b.z);
        return min;
    }

    Vector max(const Vector& a, const Vector& b) {
        Vector max;
        max.x = std::max(a.x, b.x);
        max.y = std::max(a.y, b.y);
        max.z = std::max(a.z, b.z);
        return max;
    }

    Point operator + (const Point& a, const Vector& b) {
        Point add;
        add.x = a.x + b.x;
        add.y = a.y + b.y;
        add.z = a.z + b.z;
        return add;
    }

    Point operator + (const Vector& a, const Point& b) {
        Point add;
        add.x = a.x + b.x;
        add.y = a.y + b.y;
        add.z = a.z + b.z;
        return add;
    }

    Point operator - (const Point& a, const Vector& b) {
        Point sub;
        sub.x = a.x - b.x;
        sub.y = a.y - b.y;
        sub.z = a.z - b.z;
        return sub;
    }

    Point operator * (const Float4& scale, const Point& p) {
        /* TODO */ NOT_IMPLEMENTED;
    }

}