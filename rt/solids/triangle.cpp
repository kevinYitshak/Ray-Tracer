#include <rt/solids/triangle.h>
#include <core/random.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
{
    this->p1 = vertices[1];
    this->p2 = vertices[2];
    this->p3 = vertices[3];
    this->material = material;
    if (texMapper != nullptr) this->texMapper = texMapper;

}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)

{   this->p1 = v1;
    this->p2 = v2;
    this->p3 = v3;
    this->material = material;
    if (texMapper != nullptr) this->texMapper = texMapper;
}

BBox Triangle::getBounds() const {
    Point triangle_min, triangle_max;
    
    triangle_min = rt::min(p1, rt::min(p2, p3));
    triangle_max = rt::max(p1, rt::max(p2, p3));
    
    return BBox(triangle_min, triangle_max);
}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
     // reference from Fundamentals of CG page no. 78

    float t = FLT_MAX;

    Vector edge1 = p1 - p2;
    Vector edge2 = p1 - p3;

    //p1 - ray.o - edge2 ray.d
    float det = dot(edge1, cross(edge2, ray.d));

    if (det == 0.0) { return Intersection::failure();  }

    float beta = dot((p1 - ray.o), cross(edge2, ray.d)) / det;
    float gamma = dot(edge1, cross((p1 - ray.o), ray.d)) / det;

    // stopping condition for triangle where beta + gamma = 1
    if ( beta > epsilon && gamma > epsilon && (beta + gamma) < 1.0f)
    {
        t = dot(edge1, cross(edge2, (p1 - ray.o))) / det;
        if ((epsilon < t) && ( t < previousBestDistance))
        {
            Point triangle_local = ray.getPoint(t);
            Vector triangle_normal = cross(p2 - p1, p3 - p1).normalize();
            return Intersection(t, ray, this, triangle_normal, Point((1 - beta - gamma), beta, gamma));
        }
        else
            return Intersection::failure();
    }
    else
        return Intersection::failure();


}

Solid::Sample Triangle::sample() const {
    float eps1 = random();
    float eps2 = random();

    struct Sample s;
    s.normal = cross(p2 - p1, p3 - p1).normalize();

    if (eps1 + eps2 < 1.0f)
        s.point = (1.0f - eps1 - eps2) * p1 + eps1 * p2 + eps2 * p3;
    else
        s.point = (eps1 + eps2 - 1.0f) * p1 + (1.0f - eps1) * p2 + (1.0f - eps2) * p3;

    return s;
}

float Triangle::getArea() const {
     return cross(p2 - p1, p3 - p1).length() / 2;
}

}