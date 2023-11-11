#include <core/float4.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/assert.h>
#include <core/scalar.h>

namespace rt {

    Float4::Float4(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Float4::Float4(const Point& p) {
        this->x = p.x;
        this->y = p.y;
        this->z = p.z;
        this->w = 1;
    }

    Float4::Float4(const Vector& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        this->w = 0;
    }

    float& Float4::operator [] (int idx) {
        if (idx == 0)
            return this->x;
        else if (idx == 1)
            return this->y;
        else if (idx == 2)
            return this->z;
        else if (idx == 3)
            return this->w;
    }

    float Float4::operator [] (int idx) const {
        if (idx == 0)
            return this->x;
        else if (idx == 1)
            return this->y;
        else if (idx == 2)
            return this->z;
        else if (idx == 3)
            return this->w;
    }

    Float4 Float4::operator + (const Float4& b) const {
        Float4 add;
        add.w = this->w + b.w;
        float scale_f = 1;
        add.x = this->x + b.x;
        add.y = this->y + b.y;
        add.z = this->z + b.z;
        add.w = this->w + b.w;
        return add;
    }

    Float4 Float4::operator - (const Float4& b) const {
        Float4 sub;
        sub.x = this->x - b.x;
        sub.y = this->y - b.y;
        sub.z = this->z - b.z;
        sub.w = this->w - b.w;
        return sub;
    }

    Float4 Float4::operator * (const Float4& b) const {
        Float4 mul;
        mul.x = this->x * b.x;
        mul.y = this->y * b.y;
        mul.z = this->z * b.z;
        mul.w = this->w * b.w;
        return mul;
    }

    Float4 Float4::operator / (const Float4& b) const {
        Float4 div;
        div.x = this->x / b.x;
        div.y = this->y / b.y;
        div.z = this->z / b.z;
        div.w = this->w / b.w;
        return div;
    }

    Float4 operator * (float scalar, const Float4& b) {
        Float4 scaled;
        scaled.x = b.x * scalar;
        scaled.y = b.y * scalar;
        scaled.z = b.z * scalar;
        scaled.w = b.w * scalar;
        return scaled;
    }

    Float4 operator * (const Float4& a, float scalar) {
        Float4 scaled;
        scaled.x = a.x * scalar;
        scaled.y = a.y * scalar;
        scaled.z = a.z * scalar;
        scaled.w = a.w * scalar;
        return scaled;
    }

    Float4 operator / (const Float4& a, float scalar) {
        Float4 divided;
        divided.x = (a.x) / scalar;
        divided.y = (a.y) / scalar;
        divided.z = (a.z) / scalar;
        divided.w = (a.w) / scalar;
        return divided;
    }

    float dot(const Float4& a, const Float4& b) {
        float dot;
        dot = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        return dot;
    }

    Float4 Float4::operator - () const {
        Float4 inverted;
        inverted.x = -1 * this->x;
        inverted.y = -1 * this->y;
        inverted.z = -1 * this->z;
        inverted.w = -1 * this->w;
        return inverted;
    }

    bool Float4::operator == (const Float4& b) const {
        if ((this->x == b.x) && (this->y == b.y) && (this->z == b.z) && (this->w == b.w))
        {
            return true;
        }
        return false;
    }

    bool Float4::operator != (const Float4& b) const {
        if ((this->x == b.x) && (this->y == b.y) && (this->z == b.z) && (this->w == b.w))
        {
            return false;
        }
        return true;
    }

    Float4 min(const Float4& a, const Float4& b) {
        Float4 min;
        min.x = std::min(a.x, b.x);
        min.y = std::min(a.y, b.y);
        min.z = std::min(a.z, b.z);
        min.w = std::min(a.w, b.w);
        return min;
    }

    Float4 max(const Float4& a, const Float4& b) {
        Float4 max;
        max.x = std::max(a.x, b.x);
        max.y = std::max(a.y, b.y);
        max.z = std::max(a.z, b.z);
        max.w = std::max(a.w, b.w);
        return max;
    }

}