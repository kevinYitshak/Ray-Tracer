#include <rt/textures/constant.h>

namespace rt {

ConstantTexture::ConstantTexture()
{
    c = RGBColor::rep(0.0f);
}

ConstantTexture::ConstantTexture(const RGBColor& color)
{
    c = color;
}

RGBColor ConstantTexture::getColor(const Point& coord) {
    return c;
}

RGBColor ConstantTexture::getColorDX(const Point& coord) {
    return RGBColor::rep(0.0f);
}

RGBColor ConstantTexture::getColorDY(const Point& coord) {
    return RGBColor::rep(0.0f);
}

}