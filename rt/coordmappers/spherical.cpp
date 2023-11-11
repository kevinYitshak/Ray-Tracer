#include <rt/coordmappers/spherical.h>

namespace rt {

    SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
    {
        this->origin = origin;
        this->zenith = zenith;
        this->azimuth = azimuthRef;
        this->scaleX = azimuth.length();
        this->scaleY = zenith.length();
    }

    Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    
        Vector hitvect = hit.local() - origin;

        // calculate orthogaonal axis: x-azimuth, y-zenith, z-axis
        Vector z_axis = cross(azimuth, zenith).normalize();
        Vector az_actual = azimuth; //cross(zenith, z_axis).normalize();

        // azimuthal angle == phi
        // project hitvect onto xz plane 
        Vector proj_xz = hitvect - dot(hitvect, zenith.normalize()) * zenith.normalize();

        float phi = acosf(dot(proj_xz.normalize(), az_actual.normalize()));

        // zenith angle == theta
        float theta = acosf(dot(hitvect.normalize(), zenith.normalize()));
        if (dot(hitvect, z_axis) < 0.0f) { phi = -phi; }

        return Point(phi / (2 * pi * scaleX), theta / (pi * scaleY), hitvect.length());
    }

}