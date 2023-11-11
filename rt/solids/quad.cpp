#include <rt/solids/quad.h>
#include <core/vector.h>
#include <core/random.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
{
    v1=origin;
    this->span1=span1;
    this->span2=span2;

    if (texMapper != nullptr) this->texMapper = texMapper;
    this->material=material;
}

BBox Quad::getBounds() const {

    return BBox(rt::min(v1, v1 + span1 + span2), rt::max(v1, v1 + span1 + span2));
}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {

   float t = FLT_MAX;

    // make sure spanning vector point towards the vertex v1
    Vector edge1 = -span1;
    Vector edge2 = -span2;

    // reference from Fundamentals of CG page no. 78

    float det = dot(edge1, cross(edge2, ray.d));

    if (det == 0.0) { return Intersection::failure(); }

    float beta = dot((v1 - ray.o), cross(edge2, ray.d)) / det;
    float gamma = dot(edge1, cross((v1 - ray.o), ray.d)) / det;

    // stopping condition for quad where beta and gamma should lie bw 0 & 1
    if (beta > epsilon && gamma > epsilon && (beta < 1.0f) && (gamma < 1.0f))
    {
        t = dot(edge1, cross(edge2, (v1 - ray.o))) / det;
        if ((0.0f < t) && (t < previousBestDistance))
        {
            Point triangle_local = ray.getPoint(t);
            Vector triangle_normal = cross(edge1, edge2).normalize();
            return Intersection(t, ray, this, triangle_normal, Point(beta, gamma, 0.0f));
        }
        else
            return Intersection::failure();
    }
    else
        return Intersection::failure();

   
}

Solid::Sample Quad::sample() const {
    float eps1 = rt::random();
    float eps2 = rt::random();

    struct Sample s = { v1 + eps1 * span1 + eps2 * span2, cross(span1, span2).normalize() };
    return s;
}

float Quad::getArea() const {
    return cross(span1, span2).length();
}

}
