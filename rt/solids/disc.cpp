#include <rt/solids/disc.h>
#include <core/random.h>
#include <cmath>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
    this->disc_center = center;
    this->disc_normal = normal.normalize();
    this->disc_radius = radius;
    this->material = material;
    this->texMapper = texMapper;
}

BBox Disc::getBounds() const {
    
Point disc_min, disc_max;

    disc_min = disc_center - Vector::rep(disc_radius);
    disc_max = disc_center + Vector::rep(disc_radius);

    return BBox(disc_min, disc_max);
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
    
    float t = FLT_MAX;

    if ((dot(ray.d, disc_normal)) == 0)
    {
        return Intersection::failure();
    }

    t = -dot(disc_normal, (ray.o - disc_center)) / (dot(ray.d, disc_normal));
    Point disc_local = ray.o + t * ray.d;
    if (t<0 || t>previousBestDistance)
    {
        return Intersection::failure();
    }
    if ((disc_local - disc_center).length() < disc_radius)
    {
       
       return Intersection(t, ray, this, disc_normal, disc_local);
    }
    else
    {
        return Intersection::failure();
    }


}

Vector polar2cartesian(float r, float theta, Vector n)
{
    //construct an orthogonal basis using disc normal
    float minVal = rt::min(std::abs(n.x), std::abs(n.y), std::abs(n.z));

    Vector s_;
    if (abs(minVal - n.x) <= epsilon)
        s_ = Vector(0, -n.z, n.y);
    else if (abs(minVal - n.y) <= epsilon)
        s_ = Vector(-n.z, 0, n.x);
    else if (abs(minVal - n.z) <= epsilon)
        s_ = Vector(-n.y, n.x, 0);

    Vector s = s_.normalize();
    Vector t = cross(n, s).normalize();

    float x = r * cos(theta);
    float y = r * sin(theta);

    return x * s + y * t;
}

Solid::Sample Disc::sample() const {
    float e1 = rt::random();
    float e2 = rt::random();

    Vector perturbation = polar2cartesian(e1 * disc_radius, sqrt(e2) * 2 * pi, disc_normal);
    // std::cout << n.x << " " << n.y << " " << n.z << std::endl;

    Sample sample = { disc_center + perturbation, disc_normal };

    return sample;
}

float Disc::getArea() const {
    return pi * disc_radius * disc_radius;
}

}
