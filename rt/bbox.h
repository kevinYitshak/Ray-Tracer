#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>

//---------------------------
#include <cfloat>

namespace rt {

class Ray;

class BBox {
public:
    Point min, max;
    Point center;
    BBox() {}
    BBox(const Point& min, const Point& max)
    {
        if (min != rt::min(min, max))
        {
            this->min = Point(-FLT_MAX, -FLT_MAX, -FLT_MAX);
            this->max = Point(FLT_MAX, FLT_MAX, FLT_MAX);
        }
        else
        {
            this->min = min;
            this->max = max;
        }

        // center of bounding box corresponding to primitives
        center.x = (min.x + max.x) / 2.0f;
        center.y = (min.y + max.y) / 2.0f;
        center.z = (min.z + max.z) / 2.0f;
    }

    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const {
        return max - min;
    }

    float area() const {
        
        float x = this->max.x - this->min.x;
        float y = this->max.y - this->min.y;
        float z = this->max.z - this->min.z;
        
        return 2 * ((x * y) + (y * z) + (z * x));
    }

    std::pair<float, float> intersect(const Ray& ray) const;

    bool isUnbound() const;
};

}

#endif