#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
{
    this->origin = origin;
    this->normal = normal.normalize();
    if (texMapper != nullptr) this->texMapper = texMapper;
    this->material = material;
}

BBox InfinitePlane::getBounds() const {
     return BBox::full();
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
    
    if ((dot(ray.d, normal)) == 0)
    {
        return Intersection::failure();
    }
    
    Vector ray_origin(ray.o.x, ray.o.y, ray.o.z);
    Vector plane_origin(origin.x, origin.y, origin.z);
    
    float t = (dot(plane_origin, normal) - dot(ray_origin, normal)) / (dot(ray.d, normal));
    
    if (t <= 0)
    {
        return Intersection::failure();
    }
    if (t>previousBestDistance)
    {
        return Intersection::failure();
    }
    else
    {
        return Intersection(t, ray, this, normal, ray.getPoint(t));
    }
}

Solid::Sample InfinitePlane::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float InfinitePlane::getArea() const {
    return FLT_MAX;
}

}
