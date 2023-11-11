#include <rt/cameras/orthographic.h>
#include <rt/ray.h>
#include <iostream>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
{
    /* TODO */
    c = center;
    
    sX = scaleX;
    sY = scaleY;
        
    // calculating basis vectors from up & forward ref vectors.
    this->w = - forward.normalize();
    this->v = cross(up, w).normalize();
    this->u = cross(w, v).normalize();

}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const 
{
    
    return Ray (c + (y * ( sY / 2 ) * u) + (x * (sX / 2)  * v), - w);
}

}
