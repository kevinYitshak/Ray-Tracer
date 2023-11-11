#include <rt/bbox.h>

//--------------------
#include <rt/ray.h>
#include <cfloat>

namespace rt {

BBox BBox::empty() {

    BBox bbox_empty;
    bbox_empty.min = Point(FLT_MAX, FLT_MAX, FLT_MAX);
    bbox_empty.max = Point(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    return bbox_empty;
}

BBox BBox::full() {

    BBox bbox_full;
    bbox_full.min = Point(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    bbox_full.max = Point(FLT_MAX, FLT_MAX, FLT_MAX);
    
    return bbox_full;
}


void BBox::extend(const Point& point) {
   
    min = rt::min(min, point);
    max = rt::max(max, point);
   
}

void BBox::extend(const BBox& bbox) {

    min = rt::min(min, bbox.min);
    max = rt::max(max, bbox.max);
    
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
    
    // Referred from Fundamentals of CG, page no. 302

    float ax = 1.0f / ray.d.x;
    float ay = 1.0f / ray.d.y;
    float az = 1.0f / ray.d.z;

    float t_xmin, t_ymin, t_zmin;
    float t_xmax, t_ymax, t_zmax;

    if (ax >= 0.0f)
    {
        t_xmin = ax * (this->min.x - ray.o.x);
        t_xmax = ax * (this->max.x - ray.o.x);
    }
    else
    {
        t_xmin = ax * (this->max.x - ray.o.x);
        t_xmax = ax * (this->min.x - ray.o.x);
    }
    if (ay >= 0.0f)
    {
        t_ymin = ay * (this->min.y - ray.o.y);
        t_ymax = ay * (this->max.y - ray.o.y);
    }
    else
    {   
        t_ymin = ay * (this->max.y - ray.o.y);
        t_ymax = ay * (this->min.y - ray.o.y);
    }
    if (az >= 0.0f)
    {
        t_zmin = az * (this->min.z - ray.o.z);
        t_zmax = az * (this->max.z - ray.o.z);
    }
    else
    {
        t_zmin = az * (this->max.z - ray.o.z);
        t_zmax = az * (this->min.z - ray.o.z);
    }

    float tmin = std::max(t_xmin, std::max(t_ymin, t_zmin));
    float tmax = std::min(t_xmax, std::min(t_ymax, t_zmax));

    if (tmin >= tmax)
    {
        return std::make_pair(FLT_MAX, -FLT_MAX);
    }

    return std::make_pair(tmin, tmax);


}

bool BBox::isUnbound() const {
    
    return(min.x == -FLT_MAX || min.y == -FLT_MAX || min.z == -FLT_MAX \
        || max.x == FLT_MAX || max.y == FLT_MAX || max.z == FLT_MAX);

}

}