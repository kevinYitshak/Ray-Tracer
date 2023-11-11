#include <rt/coordmappers/plane.h>

namespace rt {

    PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
        /* TODO */
        this->e1 = e1;
        this->e2 = e2;
        this->normal = cross(this->e1, this->e2);
        this->textureMatrix = Matrix::system(this->e1, this->e2, normal).invert();
    }

    Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
        /* TODO */
        Point t = textureMatrix * hit.local();
        return t;
    }

}