#include <rt/textures/imagetex.h>
#include <core/point.h>
#include <core/vector.h>
#include <cmath>

namespace rt {

ImageTexture::ImageTexture()
{
   
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
{
    this->image.readPNG(filename);
    this->bh = bh;
    this->i = i;
    //std::cout << image.width() << image.height() << std::endl;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
{
    this->image = image;
    this->bh = bh; // border handling
    this->i = i; // interpolation type
}

RGBColor ImageTexture::getColor(const Point& coord) {
    int lx = floor(coord.x);
    int ly = floor(coord.y);

    float tu, tv;

    switch (bh) {
    case ImageTexture::CLAMP:
        // clamp u
        if (coord.x <= 0.0f) { tu = 0.0f; }
        else if (coord.x >= 1.0f) { tu = 1.0f; }
        else { tu = coord.x; }
        // clmap v
        if (coord.y <= 0.0f) { tv = 0.0f; }
        else if (coord.y >= 1.0f) { tv = 1.0f; }
        else { tv = coord.y; }
        break;

    case ImageTexture::MIRROR:
        tu = coord.x - lx;
        tv = coord.y - ly;
        if (abs(lx) % 2 == 1) { tu = 1 - tu; }
        if (abs(ly) % 2 == 1) { tv = 1 - tv; }
        break;

    case ImageTexture::REPEAT:
        tu = coord.x - lx;
        tv = coord.y - ly;
        break;
    }

    float resu = image.width();
    float resv = image.height();

    float u, v, lu, lv;

    switch (i) {
    case ImageTexture::NEAREST:
        u = tu * resu;
        v = tv * resv;

        lu = std::fmin(floor(u), resu - 1.0f);
        lv = std::fmin(floor(v), resv - 1.0f);

        return image(lu, lv);

    case ImageTexture::BILINEAR:
        u = tu * (resu - 1.f); 
        v = tv * (resv - 1.f);

        lu = u - floor(u);
        lv = v - floor(v);

        float flru = floor(u);
        float flrv = floor(v);

        return (
            (1 - lu) * (1 - lv) * image(flru, flrv) +
            (1 - lu) * lv * image(flru, flrv + 1) +
            lu * (1 - lv) * image(flru + 1, flrv) +
            lu * lv * image(flru + 1, flrv + 1)
            );
    }
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    Point p1 = Point(coord.x, coord.y, 0.0f);
    Point p2 = Point(coord.x + (1.0f / image.width()), coord.y, 0.0f);
    RGBColor first = getColor(p1);
    RGBColor second = getColor(p2);
    return first - second;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    RGBColor first = getColor(Point(coord.x, coord.y, 0.0f));
    RGBColor second = getColor(Point(coord.x, coord.y + (1.0f / image.height()), 0.0f));
    return first - second;
}

}