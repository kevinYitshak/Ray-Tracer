#include <rt/solids/sphere.h>

namespace rt
{

    Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
        : center(center), radius(radius), Solid(texMapper, material)
    {
        /* TODO */
    }

    BBox Sphere::getBounds() const
    {
        Point min = Point(center.x - radius, center.y - radius, center.z - radius);
        Point max = Point(center.x + radius, center.y + radius, center.z + radius);
        return BBox(min, max);
    }

    Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const
    {
        // /* TODO */ NOT_IMPLEMENTED;
        // float distance = FLT_MAX;
        Vector oc = ray.o - center;
        float a = dot(ray.d, ray.d);
        float b = dot(oc, ray.d);
        float c = dot(oc, oc) - (radius * radius);

        float discriminant = (b * b) - (a * c);
        if (discriminant <= epsilon)
        {
            return Intersection::failure();
        }
        float discr = sqrt(discriminant);
        float d0 = (-b + discr) / (a);
        float d1 = (-b - discr) / (a);

        if (d0 < d1)
        {
            std::swap(d0, d1);
        }
        if (d1 < 0)
        {
            d1 = d0;
            if (d1 <= 0)
            {
                return Intersection::failure();
            }
        }
        if (d1 > previousBestDistance)
        {
            return Intersection::failure();
        }
        Vector normal = (ray.getPoint(d1) - this->center).normalize(); //To calculate outward normal::arrowhead(point a)-center
        return Intersection(d1, ray, this, normal, ray.getPoint(d1));
    }

    Solid::Sample Sphere::sample() const
    {
        NOT_IMPLEMENTED;
    }

    float Sphere::getArea() const
    {
        return 4 * pi * radius * radius;
    }
}
