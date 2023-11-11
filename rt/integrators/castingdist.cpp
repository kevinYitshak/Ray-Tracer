#include <rt/integrators/castingdist.h>

//------------------------------
#include <rt/intersection.h>
#include <rt/ray.h>
#include <core/vector.h>
#include <rt/world.h>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
    this->FC = farColor;
    this->NC = nearColor;
    this->FD = farDist;
    this->ND = nearDist;
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
    
    Intersection object = world->scene->intersect(ray, FLT_MAX);
    
    if (object)
    {   if ((object.distance-ND)<0)
    {
        object.distance=ND;
    }
    if ((object.distance-FD)>0)
    {
        object.distance=FD;
    }
        RGBColor color = ((FC * (object.distance - ND)) + (NC * (FD - object.distance))) / (FD - ND);
        RGBColor final_color = color.clamp() * dot(ray.d, -object.normal());
        final_color = final_color.clamp();
        return final_color;
    }
    else
    {
        return RGBColor::rep(0.0f);
    }
    
}   


}
