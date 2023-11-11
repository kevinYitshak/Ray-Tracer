#include <rt/materials/phong.h>
#include <core/vector.h>
#include <core/scalar.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
    this->specular = specular;
    this->exponent = exponent;
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    
    Vector reflDir = (inDir + 2 * dot(-inDir, normal) * normal).normalize();
    float cosTheta = dot(reflDir, outDir);
    if (cosTheta < 0.0f )
        return RGBColor::rep(0.0f);
    return specular->getColor(texPoint) * (powf(cosTheta, exponent) * (exponent + 2) * dot(normal, -inDir)) / (2 * pi);
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    
    return RGBColor::rep(0.0f);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return Material::SampleReflectance();
}

Material::Sampling PhongMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}