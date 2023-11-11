#include <rt/materials/glass.h>
#include <core/random.h>
#include <core/scalar.h>
#include <cmath>

namespace rt {

GlassMaterial::GlassMaterial(float eta)
{
    this->eta = eta;
    //this->texture = t;
}

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return RGBColor::rep(0.f);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.f); ;// texture->getColor(texPoint);
}

std::pair<double, double> GlassMaterial::fresnel(const float& cosI, const float& cosT, const float& etaI, const float& etaT) const {

    float r_parallel = ((etaT * cosI) - (etaI * cosT)) / ((etaT * cosI) + (etaI * cosT));
    float r_perpendicular = ((etaI * cosI) - (etaT * cosT)) / ((etaI * cosI) + (etaT * cosT));
    
   return std::make_pair(powf(r_parallel, 2), powf(r_perpendicular, 2));
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    
   float etaI, etaT, cosI;
    Vector n;

    // light entering: 
    if (dot(outDir, normal) > 0.0f)
    {
        etaI = 1.0f;
        etaT = eta;
        cosI = fabsf(dot(outDir, normal));
        n = normal;
    }
    // light leaving
    else
    {
        etaI = eta;
        etaT = 1.0f; // refraction indexes are reversed
        cosI = fabsf(dot(-outDir, normal));
        n = -normal; // normal is negated
    }
    
    // calculate reflected ray
    Vector R = -outDir + 2.0f * dot(outDir, normal) * normal;

    // snell law;
    float sinI = fabsf(sqrtf(1.0f - powf(cosI, 2)));
    float sinT = (etaI / etaT) * sinI;
    float cosT = fabsf(sqrtf(1.0f - powf(sinT, 2)));

    std::pair<double, double> fr = fresnel(cosI, cosT, etaI, etaT);
    float Rcolor = 0.5f * (fr.first + fr.second);
    float Tcolor = (1 - Rcolor);
	
    // total internal reflection
    if (sinT >= 1.0f)
    {
        return SampleReflectance(R.normalize(), RGBColor::rep(1.0f));
    }
    // reflection
    else if (random() < Rcolor)
    {
        return SampleReflectance(R.normalize(), RGBColor::rep(1.0f));
    }
    // refraction
    else
    {   
        // calculate transmitted ray
        Vector T = -(etaI / etaT) * outDir + (-cosT + (etaI / etaT) * cosI) * n;
        
        return SampleReflectance(T.normalize(), RGBColor::rep(1.0f));
    }

}

Material::Sampling GlassMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}