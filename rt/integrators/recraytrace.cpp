#include <rt/integrators/recraytrace.h>
#include <rt/intersection.h>
#include <rt/lights/light.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
#include <core/random.h>

namespace rt {

    RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
        
        int maxDepth = 6;
        return getRecursiveRadiance(ray, maxDepth);
    }

    RGBColor RecursiveRayTracingIntegrator::getRecursiveRadiance(const Ray& ray, int& depth) const {
        
        RGBColor totalRadiance = RGBColor::rep(0.0f);

        depth--;
        if (depth == 0)
            return totalRadiance;

        RGBColor emission, reflectance, intensity;
        Point texPoint;
        Intersection object = world->scene->intersect(ray);

        if (object) {

            texPoint = object.solid->texMapper->getCoords(object);
            Material::Sampling sampling = object.solid->material->useSampling();

            // for env solid
            if (object.distance == FLT_MAX && object.solid != nullptr)
            {
                return object.solid->material->getEmission(texPoint, object.normal(), -ray.d);
            }

            if (sampling == Material::SAMPLING_NOT_NEEDED || sampling == Material::SAMPLING_SECONDARY) {
                emission = object.solid->material->getEmission(texPoint , object.normal(), -ray.d);
                totalRadiance = totalRadiance + emission;

                for (auto light : world->light) {
                    LightHit lightHit = light->getLightHit(object.hitPoint());
                    Point r = Point(random(), random(), random());
                    //Shift the ray origin towards it's direction by an offset, to avoid self intersection
                    Ray shadowRay(object.hitPoint() + object.normal() * offset, lightHit.direction);
                    if (dot(object.normal(), shadowRay.d) > 0.0f) {
                        Intersection shaIntersec = world->scene->intersect(shadowRay, lightHit.distance);
                        //If no intersection of shadow ray, or the intersection distance greater than distance to light source, update radiance
                        if (!shaIntersec) {
                            intensity = light->getIntensity(lightHit);
                            reflectance = object.solid->material->getReflectance(texPoint, object.normal(), -ray.d, -shadowRay.d);
                            totalRadiance = totalRadiance + intensity * reflectance;
                        }
                    }
                }
            }

            if (sampling == Material::SAMPLING_ALL || sampling == Material::SAMPLING_SECONDARY) {
                Material::SampleReflectance sampleReflectance = object.solid->material->getSampleReflectance(texPoint, object.normal(), -ray.d);
                //Offset in the direction of sampleReflectance, as this would handle all cases 
                //refraction and reflection when entering or leaving the surface
                Ray secondaryRay(object.hitPoint() + sampleReflectance.direction * offset, sampleReflectance.direction);
                RGBColor radiance = getRecursiveRadiance(secondaryRay, depth);
                totalRadiance = totalRadiance + sampleReflectance.reflectance * radiance;
            }
        }
        return totalRadiance;
    }

}