#ifndef CG1RAYTRACER_SOLIDS_QUADRIC_HEADER
#define CG1RAYTRACER_SOLIDS_QUADRIC_HEADER

#include <rt/solids/solid.h>

namespace rt {

    class Material;
    class CoordMapper;

    /*
    A solid is a physical primitive that has material and can be textured
    */
    class Quadric : public Solid {
    public:
        Point quadric_center;
        float quadric_radius;
        float QA, QB, QC; // quadric axis
        bool flag_z; // true if z^2 and false for z
        Quadric() {}
        
        Quadric(const Point& center, float a, float b, float c, float radius, CoordMapper* texMapper, Material* material);

        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
        virtual Sample sample() const;
        virtual float getArea() const;
    };

}


#endif