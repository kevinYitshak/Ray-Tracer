#include <rt/materials/cooktorrance.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/scalar.h>
#include <math.h>
#include <vector>

namespace rt {
    float chiGGX(float v)
{
    return v > 0 ? 1 : 0;
}

CookTorranceMaterial::CookTorranceMaterial(
    Texture* tex, float pd, float ps, float rho, float abs_coef, float m) {
        this->pd = pd;
        this->ps = ps;
        this->rho = rho; // refractive index
        this->absorption_coefficient=abs_coef;
        this->m = m; // average slope of microfacet or roughness
        //this->alpha = alpha; // angle to avg normal of surface;
        this->tex = tex;
    }

RGBColor CookTorranceMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    Vector n = normal.normalize();
    Vector halfway = ((inDir + outDir) / 2).normalize();
    float alpha = fabsf(acosf(dot(n, halfway)));
    RGBColor clr = RGBColor::rep(0.0f);
    float D = 1/(pi*powf(m,2)*powf(cos(alpha),4))*exp(-1*(powf(tan(alpha)/m,2))); //Beckmann Equaton from slides
    Vector reflDir = (-inDir + 2 * dot(inDir, normal) * normal).normalize();
    
    float G1=1;
    float G2=2*dot(n,halfway)*dot(n,outDir)/(dot(outDir,halfway));
    float G3=2*dot(n,halfway)*dot(n,inDir)/(dot(outDir,halfway));
    float G=std::min(std::min(G1, G2), G3);
    float fresnel_term;
    float angle_with_plane=pi/2-acosf(dot(n,inDir.normalize()));
    float rparallel=((rho*rho+absorption_coefficient*absorption_coefficient)*powf(cos(angle_with_plane),2)-2*rho*cos(angle_with_plane)+1)/(((rho*rho+absorption_coefficient*absorption_coefficient)*powf(cos(angle_with_plane),2)+2*rho*cos(angle_with_plane)+1));
    float rperp=((rho*rho+absorption_coefficient*absorption_coefficient)-2*rho*cos(angle_with_plane)+powf(cos(angle_with_plane),2))/((rho*rho+absorption_coefficient*absorption_coefficient)-2*rho*cos(angle_with_plane)+powf(cos(angle_with_plane),2));
    fresnel_term=(powf(rparallel,2)+powf(rperp,2))/2;
    float ks=fresnel_term*D*G/(pi*dot(n,inDir)*dot(n,outDir));
    float cosTheta = dot(normal.normalize(), -inDir.normalize());
    float kd=fabs(cosTheta)/pi;

    
    return this->tex->getColor(texPoint)*(kd*pd+ks*ps);
}

RGBColor CookTorranceMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor(0, 0, 0);
}

Material::SampleReflectance CookTorranceMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return SampleReflectance();
}

Material::Sampling CookTorranceMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}

