#include <rt/textures/checkerboard.h>
#include <cmath>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
{
    this->w = white;
    this->b = black;
}

// Point coord == object.local()
RGBColor CheckerboardTexture::getColor(const Point& coord) {
    // Multiply by 2 to reduce edge length from 1 to 0.5
    int lu = floor(coord.x * 20);
    int lv = floor(coord.y * 20);
    int lw = floor(coord.z * 20);

    int p = abs(lu + lv + lw) % 2;
    if (p == 1) { return b; }
    return w;
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    return RGBColor::rep(0.0f);
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    return RGBColor::rep(0.0f);
}

}