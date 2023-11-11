#include <rt/coordmappers/spherical.h>

#include <core/matrix.h>
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
    
        // Vector hitvect = hit.hitPoint() - origin;

        // calculate orthogaonal axis: x-azimuth, y-zenith, z-axis
        Vector z_axis = cross(azimuth,zenith);
        Vector x_new=cross(z_axis,zenith);
        
        Matrix texture_transform=product(Matrix::system(x_new,this->zenith,z_axis),Matrix(Float4(0,0,0,(this->origin.x)),Float4(0,0,0,(this->origin.y)),Float4(0,0,0,(this->origin.z)),Float4(0,0,0,1)));

        // azimuthal angle == phi
        // project hitvect onto xz plane 
        Vector transformed_hitvect=(texture_transform*hit.hitPoint())-Point(0,0,0);
        transformed_hitvect=transformed_hitvect;
        
        float u = (pi+atan2f(transformed_hitvect.y,transformed_hitvect.x))/(2*pi);

        // zenith angle == theta
        float v = (pi-acosf(transformed_hitvect.z/abs(transformed_hitvect.x)))/pi;
        
        return Point(u, v,0);
    }

}