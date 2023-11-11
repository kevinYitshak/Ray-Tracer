
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/solids/sphere.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <chrono>
#include <stdio.h>
#include <iostream>
using namespace rt;

void a_indexing() {
    
    
   Image img(800, 600);

    BVH* scene = new BVH();
    // scene->add(new Sphere(Point(2.5f,  .5f,  -1), 0.5  , nullptr, nullptr));
    // scene->add(new Sphere(Point(2.5f,  -1.f,  -1), 0.5, nullptr, nullptr));
   //  scene->add(new Sphere(Point(4.5f,  .5f,  -1), 0.5 , nullptr, nullptr));

    loadOBJ(scene, "models/", "cow.obj", nullptr);
  
	scene->rebuildIndex();
    World world;
    world.scene = scene;

    PerspectiveCamera cam1(Point(7.358891, 1.073871, 5.883171),(Point(6.472916, 1.258473, 5.457766)-Point(7.358891, 1.073871, 5.883171)), Vector(-0.462404, -0.421054, 0.780318), pi/3, pi/3);
    //PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f)-Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi/8, pi/6);
    RayCastingIntegrator integrator(&world);
    Renderer engine1(&cam1, &integrator);
    auto begin = std::chrono::high_resolution_clock::now();
    engine1.render(img);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    std::cout << "Time measured: i1 " << elapsed.count() * 1e-9 << " seconds." << std::endl;
    img.writePNG("a3-1.png");
    
    //Renderer engine2(&cam2, &integrator);
    //engine2.render(img);
    //img.writePNG("a3-2.png");
}
