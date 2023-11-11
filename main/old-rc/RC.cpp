#include <core/image.h>
#include <core/color.h>
#include <core/random.h>

#include <rt/world.h>   
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/integrators/recraytrace.h>
#include <rt/integrators/casting.h>
// Group
#include <rt/groups/simplegroup.h>
#include <rt/groups/bvh.h>
//Camera
#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>
//Solids
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/solids/triangle.h>
#include <rt/solids/disc.h>
#include <rt/solids/env.h>
//Texture
#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/perlin.h>
#include <rt/textures/checkerboard.h>
// Coord Mappers
#include <rt/coordmappers/env.h>
// Materials
#include <rt/materials/flatmaterial.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/glass.h>
#include <rt/materials/phong.h>
#include <rt/materials/combine.h>
#include <rt/materials/combineTex.h>
#include <rt/materials/mirror.h>
#include <rt/materials/dummy.h>
// Lights
#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>
#include <rt/lights/spotlight.h>
// Primod
#include <rt/primmod/instance.h>

#include <chrono>
#include <algorithm>

using namespace rt;


MatLib* getOuterCube() {

    MatLib* cube = new MatLib;

    Texture* t = new ImageTexture("models/plank.png");
    Texture* black = new ConstantTexture(RGBColor::rep(0.0f));
    Material* mat = new LambertianMaterial(black, t);
    cube->insert(std::pair<std::string, Material*>("Material", mat));

    return cube;
}

MatLib* getPlank() {

    MatLib* plank = new MatLib;
    Texture* black1 = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* t = new ImageTexture("models/green_table.png");
    Material* plank_mat = new LambertianMaterial(black1, t);

    plank->insert(std::pair<std::string, Material*>("Plank.001", plank_mat));
    
    return plank;
}

MatLib* getCandle() {
    
    MatLib* candle = new MatLib;

    ImageTexture* t = new ImageTexture("models/candle2.png");
    Material* candle_mat = new FlatMaterial(t);
    candle->insert(std::pair<std::string, Material*>("candle", candle_mat ));
    return candle;
}

MatLib* getPumpkin() {

    MatLib* pumpkin = new MatLib;

    ImageTexture* base = new ImageTexture("models/base.png");
    ImageTexture* emis = new ImageTexture("models/emission.png");
    Texture* black = new ConstantTexture(RGBColor::rep(0.0f));

    Material* stem_mat = new LambertianMaterial(black, base);
    Material* pumpkin_mat = new FlatMaterial(base);
    pumpkin->insert(std::pair<std::string, Material*>("P_Stem_Mat", stem_mat));
    pumpkin->insert(std::pair<std::string, Material*>("Pumpkin_Mat", pumpkin_mat));
    return pumpkin;
}

MatLib* getMushroom() {

    MatLib* mushroom = new MatLib;

    ImageTexture* t = new ImageTexture("models/mushroom.png");
    Texture* black = new ConstantTexture(RGBColor::rep(0.0f));
    Material* lab_mat = new LambertianMaterial(black, t);
    mushroom->insert(std::pair<std::string, Material*>("lambert2SG", lab_mat));
    mushroom->insert(std::pair<std::string, Material*>("pasted__lambert2SG2", lab_mat));
    mushroom->insert(std::pair<std::string, Material*>("pasted__pasted__lambert2SG2", lab_mat));

    return mushroom;
}

MatLib* getCandleGlass1() {

    MatLib* glass = new MatLib;
    ConstantTexture* t2 = new ConstantTexture(RGBColor(103.f, 213.f, 246.f) / 255.f);

    CombineMaterialTex* m = new CombineMaterialTex();
    m->add(new GlassMaterial(1.45f), t2, .7f);
    m->add(new GlassMaterial(1.45f), nullptr, 0.3f);

    glass->insert(std::pair<std::string, Material*>("Glass", m));
    return glass;
}

MatLib* getCandleGlass2() {

    MatLib* glass = new MatLib;
    ConstantTexture* t2 = new ConstantTexture(RGBColor(103.f, 246.f, 189.f) / 255.f);
    CombineMaterialTex* m = new CombineMaterialTex();
    m->add(new GlassMaterial(1.45f), t2, .7f);
    m->add(new GlassMaterial(1.45f), nullptr, 0.3f);

    glass->insert(std::pair<std::string, Material*>("Glass", m));
    return glass;
}

MatLib* getCandleGlass3() {

    MatLib* glass = new MatLib;
    
    ConstantTexture* t2 = new ConstantTexture(RGBColor(246.f, 103.f, 103.f) / 255.f);

    CombineMaterialTex* m = new CombineMaterialTex();
    m->add(new GlassMaterial(1.45f), t2, .7f);
    m->add(new GlassMaterial(1.45f), nullptr, 0.3f);

    glass->insert(std::pair<std::string, Material*>("Glass", m));
    return glass;
}

MatLib* getGhost() {

    MatLib* ghost = new MatLib;

    ImageTexture* t = new ImageTexture("models/candle2.png");
    Texture* black = new ConstantTexture(RGBColor::rep(0.0f));
    Material* lab_ghost = new LambertianMaterial(black, t);
    Material* flat_ghost = new FlatMaterial(t);

    ghost->insert(std::pair<std::string, Material*>("Material.007", lab_ghost));
    ghost->insert(std::pair<std::string, Material*>("Material.008", flat_ghost));

    return ghost;
}

MatLib* getFlame() {

    MatLib* flame = new MatLib;

    ImageTexture* t = new ImageTexture("models/flame.png");
    Material* flame_mat = new FlatMaterial(t);
    flame->insert(std::pair<std::string, Material*>("Material.004", flame_mat));
    
    return flame;
}

MatLib* getAnt() {

    MatLib* ant = new MatLib;

    Texture* t = new ImageTexture("models/ant.png");
    Texture* black = new ConstantTexture(RGBColor::rep(0.0f));
    Material* mat = new LambertianMaterial(black, t);
    ant->insert(std::pair<std::string, Material*>("Ant", mat));
    
    return ant;
}

MatLib* getSpider() {

    MatLib* spider = new MatLib;

    Texture* t = new ImageTexture("models/s.png");// new ConstantTexture(RGBColor::rep(0.0f));
    Texture* black = new ConstantTexture(RGBColor::rep(0.0f));
    Texture* white = new ConstantTexture(RGBColor::rep(1.0f));
    Material* mat = new LambertianMaterial(black, t);
    Material* eye = new FlatMaterial(white);
    spider->insert(std::pair<std::string, Material*>("body_initialShadingGroup", mat));
    spider->insert(std::pair<std::string, Material*>("eyes_initialShadingGroup", eye));
    spider->insert(std::pair<std::string, Material*>("leg1_initialShadingGroup", mat));

    return spider;
}

MatLib* getSpiderWeb() {

    MatLib* spider_web = new MatLib;

    Texture* t = new ImageTexture("models/candle2.png");
    Texture* white = new ConstantTexture(RGBColor::rep(1.0f));
    Texture* grey = new ConstantTexture(RGBColor(114.f, 112.f, 112.f) / 125.f); // grey
    Texture* black = new ConstantTexture(RGBColor::rep(0.0f));
    Material* mat = new FlatMaterial(t);
    spider_web->insert(std::pair<std::string, Material*>("Material", mat));

    return spider_web;
}

MatLib* getMirror() {
    MatLib* mirror = new MatLib;

    Texture* t1 = new ImageTexture("models/candle2.png");
    ConstantTexture* t2 = new ConstantTexture(RGBColor(164.f, 30.f, 232.f) / 255.f);
    CombineMaterialTex* m = new CombineMaterialTex();
    m->add(new GlassMaterial(1.45f), t1, 0.5f);
    //m->add(new GlassMaterial(1.45f), t2, 0.2f);
    m->add(new GlassMaterial(1.45f), nullptr, 0.5f);
    //m->add(new FlatMaterial(t1), nullptr, 0.1f);
    mirror->insert(std::pair<std::string, Material*>("Glass_mirror", new GlassMaterial(1.45f)));
    return mirror;
}

MatLib* getFrame() {

    MatLib* frame = new MatLib;
    ImageTexture* t = new ImageTexture("models/plank.png");
    Texture* black = new ConstantTexture(RGBColor::rep(0.0f));
    Material* frame_mat = new LambertianMaterial(black, t);
    frame->insert(std::pair<std::string, Material*>("Plank", frame_mat));
    
    return frame;
}

MatLib* getLeaf() {

    MatLib* leaf = new MatLib;
    Texture* black1 = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* t = new ImageTexture("models/leaf1.png");
    Material* leaf_mat = new LambertianMaterial(black1, t);
    leaf->insert(std::pair<std::string, Material*>("daun", leaf_mat));

    return leaf;
}

MatLib* getPlant() {

    MatLib* plant = new MatLib;

    Texture* black1 = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* t = new ImageTexture("models/green_table.png");
    Material* plant_mat = new LambertianMaterial(black1, t);

    plant->insert(std::pair<std::string, Material*>("Material__85", plant_mat));

    return plant;
}

MatLib* getPlantJar() {

    MatLib* jar = new MatLib;
    Texture* t1 = new ImageTexture("models/candle2.png");
    ConstantTexture* t2 = new ConstantTexture(RGBColor(237.f, 255.f, 70.f) / 255.f);
    CombineMaterialTex* m = new CombineMaterialTex();
    //m->add(new GlassMaterial(1.45f), t1, 0.3f);
    m->add(new GlassMaterial(1.45f), t2, 0.9f);
    m->add(new GlassMaterial(1.45f), nullptr, 0.1f);
    //m->add(new FlatMaterial(t1), nullptr, 0.1f);
    
    jar->insert(std::pair<std::string, Material*>("Material__79", m));

    return jar;
}

void RC() {

    //Image img(1440, 1440);
    Image img(1440, 1440);

    std::cout << "Resolution is " << img.width() << ", " << img.height() << std::endl;
    World world;
    BVH* scene = new BVH();
    //world.scene = scene;
    SimpleGroup* simple_scene = new SimpleGroup();
    world.scene = simple_scene;

    // OuterCube
    // MatLib* cube = getOuterCube();
    // loadOBJ(scene, "models/", "outer_cube.obj", nullptr, cube);
    
    // //objects
    ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ConstantTexture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    LambertianMaterial white(blacktex, whitetex);

     MatLib* plank = getPlank();
    Texture* bplank = new ImageTexture("models/candle2.png");
    loadOBJ(scene, "models/", "plank.obj", bplank, plank);

    MatLib* candleglass1 = getCandleGlass1();
    loadOBJ(scene, "models/", "glass1.obj", nullptr, candleglass1);
    MatLib* candleglass2 = getCandleGlass2();
    loadOBJ(scene, "models/", "glass2.obj", nullptr, candleglass2);
    MatLib* candleglass3 = getCandleGlass3();
    loadOBJ(scene, "models/", "glass3.obj", nullptr, candleglass3);

    // MatLib* candle = getCandle();
    // loadOBJ(scene, "models/", "candle2.obj", nullptr, candle);

    // MatLib* flame = getFlame();
    // loadOBJ(scene, "models/", "candle_flame2.obj", nullptr, flame);

    // MatLib* jar = getPlantJar();
    // loadOBJ(scene, "models/", "PlantJar.obj", nullptr, jar);

    // MatLib* plant = getPlant();
    // loadOBJ(scene, "models/", "Plant.obj", nullptr, plant);

    MatLib* ghost = getGhost();
    Texture* bghost = new ImageTexture("models/bghost.png");
    loadOBJ(scene, "models/", "ghost.obj", nullptr, ghost);

    // MatLib* pumpkin = getPumpkin();
    // //Texture* bpumpkin = new ImageTexture("models/pbmap.png");
    // loadOBJ(scene, "models/", "pumpkin.obj", nullptr, pumpkin);

    // MatLib* mushroom = getMushroom();
    // loadOBJ(scene, "models/", "mushroom.obj", nullptr, mushroom);

    // MatLib* ant = getAnt();
    // loadOBJ(scene, "models/", "ant.obj", nullptr, ant);

    // MatLib* spider = getSpider();
    // loadOBJ(scene, "models/", "spider.obj", nullptr, spider);

    // MatLib* spiderweb = getSpiderWeb();
    // loadOBJ(scene, "models/", "spider_web.obj", nullptr, spiderweb);

    // MatLib* mirror = getMirror();
    // loadOBJ(scene, "models/", "mirror.obj", nullptr, mirror);

    // MatLib* frame = getFrame();
    // loadOBJ(scene, "models/", "mirrorframe.obj", nullptr, frame);

    // MatLib* leaf = getLeaf();
    // loadOBJ(scene, "models/", "leaf1.obj", nullptr, leaf);

    //Lighting
    // RGBColor lightColor = RGBColor(1.0,0.99,0.98);
    RGBColor lightColor1 = RGBColor(155.f, 27.f,240.f) / 255.f; // Violet 84.f, 151.f, 179.f
    RGBColor lightColor2 = RGBColor(208.f, 37.f, 27.f) / 255.f; // red
    RGBColor lightColor3 = RGBColor(0.459f, 1.0f, 0.557); // green
    RGBColor lightColor4 = RGBColor(20.f, 162.f,223.f) / 255.f;

    Point lightorigin1 = Point(-0.153696, 0.188144, -0.452985); // left 
    Point lightorigin2 = Point(-0.085858, 0.249287, 0.258221); // right
    Point lightorigin3 = Point(0.20908, 0.162299, -0.181175); // behind pumpkin
    Point lightorigin4 = Point(0.281477, 0.38586, -0.150193); // top 
    Point lightoriginspot = Point(0.405538, 0.393502, -0.452514);
    //world.light.push_back(new PointLight(lightorigin1, lightColor1 / 2.f));
    //world.light.push_back(new PointLight(lightorigin2, lightColor2 / 2.f));
    //world.light.push_back(new PointLight(lightorigin3, lightColor3 / 8.f));
    //world.light.push_back(new PointLight(lightorigin4, lightColor3 / 8.f));

    world.light.push_back(new SpotLight(lightoriginspot, Vector(0, -1, 0), pi, 1.0f, lightColor3 / 10.0f));

    Vector s1 =  Vector(-0.1, 0, 0);
    Vector s2 =  Vector(0, 0, 0.1);

    // Left
    ConstantTexture* lightsrctex = new ConstantTexture(lightColor1 * 200);
    Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);
    Quad* light = new Quad(lightorigin1, s1, s2, nullptr, lightsource);
    AreaLight als(light);
    world.light.push_back(&als);
    scene->add(light);
    // Right
    ConstantTexture* lightsrctex1 = new ConstantTexture(lightColor2 * 50);
    Material* lightsource1 = new LambertianMaterial(lightsrctex1, blacktex);
    Quad* light1 = new Quad(lightorigin2, s1, s2, nullptr, lightsource1);
    AreaLight als1(light1);
    world.light.push_back(&als1);
    //scene->add(light1);
    // Midlle
    ConstantTexture* lightsrctex2 = new ConstantTexture(lightColor3 * 10);
    Material* lightsource2 = new LambertianMaterial(lightsrctex2, blacktex);
    Quad* light2 = new Quad(lightorigin3, s1, s2, nullptr, lightsource2);
    AreaLight als2(light2);
    world.light.push_back(&als2);
    // Top
    ConstantTexture* lightsrctex3 = new ConstantTexture(lightColor3 * 20);
    Material* lightsource3 = new LambertianMaterial(lightsrctex3, blacktex);
    Quad* light3 = new Quad(lightorigin4, s1, s2, nullptr, lightsource3);
    AreaLight als3(light3);
    world.light.push_back(&als3);
    //scene->add(light3);

    // Main Camera
    Point origin = Point(-0.440937, 0.179126, 0.304117);
    Vector forward = Point(0.360052, 0.026347, -0.274741) - origin;
    Vector up = Vector(0.128320, 0.988231, -0.083263);
    DOFPerspectiveCamera* cam = new DOFPerspectiveCamera(origin, forward, up, 28.84 * pi / 180, 28.84 * pi / 180, 0.6f, 0.005f); // clear - 1.6924f
    //PerspectiveCamera* cam = new PerspectiveCamera(origin, forward, up, 28.84 * pi / 180, 28.84 * pi / 180);

    //RayCastingIntegrator integrator(&world);
    RecursiveRayTracingIntegrator integrator(&world);
    scene->rebuildIndex();

    simple_scene->add(scene);
    // Environment 
    ImageTexture* envtex = new ImageTexture("models/s1.png");
    Material* env = new FlatMaterial(envtex);
    simple_scene->add(new Environment(new EnvironmentMapper, env));

    Renderer engine(cam, &integrator);
    engine.setSamples(3);
    
    auto begin = std::chrono::high_resolution_clock::now();
    engine.render(img);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    std::cout << "Time measured: i1 " << elapsed.count() * 1e-9 << " seconds." << std::endl;
    
    img.writePNG("scene_wo_smooth.png");
}