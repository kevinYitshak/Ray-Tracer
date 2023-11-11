#include <rt/solids/quadric.h>

namespace rt {

    Quadric::Quadric(const Point& center, float AxisA, float AxisB, float AxisC, float radius, CoordMapper* texMapper, Material* material)
    {
        this->quadric_center = center;
        this->quadric_radius = radius;
        this->QA = AxisA;
        this->QB = AxisB;
        this->QC = AxisC;

        //assert (QA > 0.0f && QB > 0.0f && QC > 0.0f) << "Give input axis values > 0.0f";
    }

    BBox Quadric::getBounds() const {
        /* TODO */ NOT_IMPLEMENTED;
    }

    Intersection Quadric::intersect(const Ray& ray, float previousBestDistance) const {
        // General Equation:
        
        // ((x - xc)^2 / QA^2) + ((y - yc)^2 / QB^2) + ((z - zc)^2 / QC^2) = R^2;
        
        // At^2 + Bt + C = 0 and solve for t 
        
        float t = FLT_MAX;

        float a = 1 / sqr(QA); float b = 1 / sqr(QB); float c = 1 / sqr(QC);
        
        float g = -2 * (quadric_center.x) * a;
        float h = -2 * (quadric_center.y) * b;
        float i = -2 * (quadric_center.z) * c;

        float j = (sqr(quadric_center.x) * a) + (sqr(quadric_center.y) * b) + (sqr(quadric_center.z) * c) - sqr(quadric_radius);
        
        // (a*xd^2 + b*yd^2 + c*zd^2)
        float A = a * sqr(ray.d.x) + b * sqr(ray.d.y) + c * sqr(ray.d.z);
         
        // 2 * (a*xd*xo + b*yd*yo + c*zd*zo)
        float B1 = 2 * ((a * ray.d.x * ray.o.x) + (b * ray.d.y * ray.o.y) + (c * ray.d.z * ray.o.z));
        float B2 = (g * ray.d.x) + (h * ray.d.y) + (i * ray.d.z);
        float B = B1 + B2;

        // (a*xo^2 + b*yo^2 + c*zo^2) + (g*xo + h*yo + z*zo) 
        float C = (a * sqr(ray.o.x) + (b * sqr(ray.o.y)) + (c * sqr(ray.o.z))) + (g * ray.o.x) + (h * ray.o.y) + (i * ray.o.z);

        float discriminant = B * B - 4.0f * A * C;

        if (discriminant >= 0.0f)
        {
            float t1 = (-B + sqrtf(discriminant)) / (2.0f * A);
            float t2 = (-B - sqrtf(discriminant)) / (2.0f * A);

            if (min(t1, t2) < previousBestDistance && min(t1, t2) > epsilon)
            {
                float t = min(t1, t2);
                Point quadric_local = ray.o + t * ray.d;
                
                Vector quadric_normal;
                quadric_normal.x = 2 * (a * quadric_local.x) + g;
                quadric_normal.y = 2 * (b * quadric_local.y) + h;
                quadric_normal.z = 2 * (c * quadric_local.z) + i;
                return Intersection(t, ray, this, quadric_normal.normalize(), quadric_local);
            }
            else if (min(t1, t2) < 0.0f)
            {
                return Intersection::failure();
            }

        }
        else
        {
            return Intersection::failure();
        }




    }

    Solid::Sample Quadric::sample() const {
        NOT_IMPLEMENTED;
    }

    float Quadric::getArea() const {
        /* TODO */ NOT_IMPLEMENTED;
    }

}
