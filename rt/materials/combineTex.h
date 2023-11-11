#ifndef CG1RAYTRACER_MATERIALS_COMBINETEX_HEADER
#define CG1RAYTRACER_MATERIALS_COMBINETEX_HEADER

#include <rt/materials/material.h>
#include <rt/primitive.h>
#include <rt/textures/texture.h>
#include <vector>
#include <utility>

namespace rt {

    class CombineMaterialTex : public Material {
    public:
        CombineMaterialTex();
        void add(Material* material, Texture* tex, float w);
        virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
        virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
        virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
        virtual Sampling useSampling() const;

    private:
        std::vector<std::pair<Material*, std::pair<Texture*, float>>> materials;
    };

}

#endif