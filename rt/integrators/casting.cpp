#include <rt/integrators/casting.h>

//------------------------------
#include <rt/intersection.h>
#include <rt/ray.h>
#include <core/vector.h>
#include <rt/world.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO  NOT_IMPLEMENTED; */

    // Find the intersection bw the ray and the scene
    // if it hits the objects in the scene, it should 
    // reutrn a gray color = dot(ray.d, hit surface normal)
    
    Intersection object = world->scene->intersect(ray, FLT_MAX);

    float gray_value = 0.0f;
    if (object)
    {
        
        gray_value = dot(ray.d, -object.normal());
        gray_value = gray_value < 0 ? 0 : gray_value;
    } 
    
    return RGBColor::rep(gray_value);
    
}

}
