#ifndef CG1RAYTRACER_MATERIALS_GLASS_HEADER
#define CG1RAYTRACER_MATERIALS_GLASS_HEADER

#include <rt/materials/material.h>
#include <utility>
#include <rt/textures/texture.h>

namespace rt {

class GlassMaterial : public Material {
public:
    GlassMaterial(float eta);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;

    std::pair<double, double> fresnel(const float& cosI, const float& cosT, const float& etaI, const float& etaT) const;
    
    Vector refract(const Vector I, const Vector& N, const float& ior) const;
    float fresnel(const Vector I, const Vector& N, const float& ior) const;

private:
    float eta;
    //Texture* texture;
};

}

#endif