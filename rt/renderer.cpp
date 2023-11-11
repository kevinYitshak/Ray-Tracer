#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <iostream>

//------------------------------------
#include <rt/cameras/camera.h>
#include <rt/integrators/integrator.h>
#include <core/random.h>
// Multithreading


namespace rt {

    Renderer::Renderer(Camera* cam, Integrator* integrator)
        : cam(cam), integrator(integrator), samples(1)
    {}
    // collapse(2) schedule(dynamic)
    void Renderer::render(Image& img) {


#pragma omp parallel for collapse(2) schedule(dynamic)
        for (int i = 0; i < img.width(); i++)
        {
            for (int j = 0; j < img.height(); j++)
            {
                RGBColor radiance = RGBColor::rep(0.0f);
                float ndcx, ndcy;
                for (int iter = 0; iter < this->samples; iter++)
                {
                    if (this->samples == 1)
                    {
                        ndcx = (i + 0.5) / img.width();
                        ndcy = (j + 0.5) / img.height();
                    }
                    else
                    {
                        //super sampling
                        ndcx = (i + random()) / img.width();
                        ndcy = (j + random()) / img.height();
                    }

                    /* Screen space co-ordinates*/
                    float sscx = (ndcx * 2) - 1;
                    float sscy = 1 - (ndcy * 2);

                    rt::Ray r = cam->getPrimaryRay(sscx, sscy);
                    radiance = radiance + integrator->getRadiance(r);
                }

                // get Radiance returns RGBColor
                img(i, j) = (radiance / this->samples);

            }
        }
    }

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

    void Renderer::test_render1(Image& img) {

        for (uint i = 0; i < img.height(); i++)
        {
            for (uint j = 0; j < img.width(); j++)
            {
                img.operator()(i, j) = a1computeColor(i, j, img.width(), img.height());
            }
        }
    }
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

    void Renderer::test_render2(Image& img)
    {

        for (uint i = 0; i < img.height(); i++)
        {
            for (uint j = 0; j < img.width(); j++)
            {
                /* Normalized co-ordinates */
                float ndcx = (i + 0.5) / img.height();
                float ndcy = (j + 0.5) / img.width();

                /* Screen space co-ordinates*/
                float sscx = (ndcx * 2) - 1;
                float sscy = 1 - (ndcy * 2);

                Ray r = this->cam->getPrimaryRay(sscx, sscy);

                img(i, j) = a2computeColor(r);

            }
        }

    }

}