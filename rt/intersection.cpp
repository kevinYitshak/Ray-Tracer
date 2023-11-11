#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{  
    // distance = t
    // Ray ray: ray which was used for intersection.
    // Solid solid: primitive object hit by the ray.
    // Vector normal: normal vector at hit position.
    // Point local: object-space co-or of the hit point. 
    // local co-or depends upon type of the obj that was hit.
    // Eg. for triangle/quad, the local co-or are barycentric co-or

    this->distance = distance;
    this->ray = ray;
    this->solid = solid;
    this->normal_vec = normal;
    this->local_point = local;
}

Intersection::operator bool() const {
    
    // return false if no intersection.
    /*if (Intersection::distance == FLT_MAX)
    {
        return false;
    }
    else
        return true;*/

    if (Intersection::solid == nullptr) { return false; }
    else { return true; }
}

Intersection Intersection::failure() {
    
    // no intersection occurred

    Intersection fail;
    //fail.distance = FLT_MAX;
    fail.solid = nullptr;
    return fail;

}

Point Intersection::hitPoint() const {

    return this->ray.getPoint(this->distance);

}

Vector Intersection::normal() const {
    
    return this->normal_vec;
}

Point Intersection::local() const {
    
    return this->local_point;
}

}
