#include <rt/coordmappers/cylindrical.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
{
    this->origin = origin;
    this->la = longitudinalAxis;
    this->pa = polarAxis;
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    
    Vector hitvect = hit.local() - origin;
    Vector z_axis = cross(pa, la).normalize();
    Vector pa_ = cross(la, z_axis).normalize();

    // calculate phi
    Vector proj_xz = hitvect - dot(hitvect, la.normalize()) * la.normalize();
    float phi = acosf(dot(proj_xz.normalize(), pa_.normalize()));
    if (dot(hitvect, z_axis) < 0.0f) { phi = -phi; }
    // height
    float height = dot(hitvect, la.normalize());
    
    return Point(phi / (2 * pi * pa.length()), height / la.length() , hitvect.length());
}

}