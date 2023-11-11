#include <rt/materials/combineTex.h>
#include <core/random.h>

namespace rt {

    CombineMaterialTex::CombineMaterialTex()
    {
        /* TODO */
    }

    void CombineMaterialTex::add(Material* m, Texture* t, float w) {
        materials.push_back(std::make_pair(m, std::make_pair(t, w)));
    }

    RGBColor CombineMaterialTex::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
        RGBColor reflectance = RGBColor::rep(0.f);
        for (auto m : materials) {
            if (m.second.first == nullptr)
                reflectance = reflectance + m.first->getReflectance(texPoint, normal, outDir, inDir) * m.second.second;
            else
                reflectance = reflectance + m.first->getReflectance(texPoint, normal, outDir, inDir) * m.second.first->getColor(texPoint);
        }

        return reflectance;
    }

    RGBColor CombineMaterialTex::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
        RGBColor emissions = RGBColor::rep(0.f);
        for (auto m : materials) {
            if (m.second.first == nullptr)
                emissions = emissions + m.first->getEmission(texPoint, normal, outDir) * m.second.second;
            else
                emissions = emissions + m.first->getEmission(texPoint, normal, outDir) * m.second.first->getColor(texPoint);
        }

        return emissions;
    }

    Material::SampleReflectance CombineMaterialTex::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

        SampleReflectance sampleRef;
        RGBColor r = RGBColor::rep(0.f);
        RGBColor r1 = RGBColor::rep(0.f);
        for (auto m : materials) {
            sampleRef = m.first->getSampleReflectance(texPoint, normal, outDir);
            //if (m.second.first == nullptr)
            //    r = r + sampleRef.reflectance * m.second.second; // weight the reflectance.
            //else
            //    r = r + sampleRef.reflectance * m.second.first->getColor(texPoint); // weight the reflectance.

            RGBColor c;
            if (m.second.first == nullptr) { c = RGBColor::rep(1.0f); }
            else { c = m.second.first->getColor(texPoint); }
            
            if ( m.second.first == nullptr)
            {
                r = r + sampleRef.reflectance * m.second.second;
            }
            else
            {   
                RGBColor s = sampleRef.reflectance;
                r1 = r1 + c * m.second.second;
            }
        }
        
        return SampleReflectance(sampleRef.direction, (r+r1));
    }

    Material::Sampling CombineMaterialTex::useSampling() const {
        return SAMPLING_SECONDARY;
    }

}