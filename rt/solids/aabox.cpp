#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
    this->corner1=corner1;
    this->corner2=corner2;
    this->texMapper=texMapper;
    this->material=material;
}

BBox AABox::getBounds() const {
    Point AABox_min, AABox_max;

    AABox_min = rt::min(corner1, corner2);
    AABox_max = rt::max(corner1, corner2);

    return BBox(AABox_min, AABox_max);
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
    float tmin=(corner1.x-ray.o.x)/ray.d.x;
    Vector normal(1,0,0);
    normal=normal*-1;
    int dir_normal_x=-1, dir_normal_y=-1,dir_normal_z=-1;
    float tmax=(corner2.x-ray.o.x)/ray.d.x;
    if (tmin>tmax)
    {
        std::swap(tmin,tmax);
        normal=normal*-1;
    }
    float tminy=(corner1.y-ray.o.y)/ray.d.y;
    float tmaxy=(corner2.y-ray.o.y)/ray.d.y;
    if (tminy>tmaxy)
    {
        std::swap(tminy,tmaxy);
        dir_normal_y=1;
    }
    
    if ((tmin > tmaxy) || (tminy > tmax)) 
        return Intersection::failure(); 

 
    if (tminy > tmin) 
        {tmin = tminy; 
        normal=dir_normal_y*Vector(0,1,0);}
 
    if (tmaxy< tmax) 
        tmax = tmaxy; 
    float tminz=(corner1.z-ray.o.z)/ray.d.z;
    float tmaxz=(corner2.z-ray.o.z)/ray.d.z;
    if (tminz>tmaxz)
    {
        std::swap(tminz,tmaxz);
        dir_normal_z=1;
    }

    if (tmin > tmaxz || (tminz > tmax)) 
        return Intersection::failure(); 
 
    if (tminz> tmin) 
        {tmin = tminz;
        normal=dir_normal_z*Vector(0,0,1);
        } 
 
    if (tmaxz < tmax) 
        tmax = tmaxz; 
    if (tmin>previousBestDistance)
    {
        return Intersection::failure();
    }
    if (tmin<0)
    {
        return Intersection::failure();
    }
 
    return Intersection(tmin,ray,this,normal,ray.getPoint(tmin)); 

    


}
}