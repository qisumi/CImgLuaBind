#include <iostream>
#include <CImg.h>
#include <lua.hpp>
#include "LuaBridge3.h"

using namespace cimg_library;
using namespace luabridge;

void BindImgFormats(lua_State* L)
{
    using ImgUInt8 = CImg<uint8_t>;
    using ImgDouble = CImg<double>;
    using ImgFloat = CImg<float>;

#define BIND_IMG_FORMAT(format, fmtname, L) \
getGlobalNamespace(L)\
.beginClass<format>(fmtname)\
.addConstructor<void()>()\
.addFunction("clone", +[](format *img, const format &target) { return *img = target; })\
.addFunction("width", +[](format *img) { return img->width(); })\
.addFunction("height", +[](format *img) { return img->height(); })\
.addFunction("resize", +[](format *img, int x, int y, int z, int c) { return img->resize(x, y, z, c); })\
.addFunction("setGray", +[](format *img) { return img->channel(0); })\
.addFunction("fill", +[](format *img, const int v) { return img->fill(v); })\
.addFunction("loadBmp", +[](format *img, const char *name) { return img->load_bmp(name); })\
.addFunction("display", +[](format *img, const char *title) { return img->display(title, false); })\
.addFunction("getXY", +[](format *img, int x, int y) { return img->atXY(x, y); })\
.addFunction("getXYC", +[](format *img, int x, int y, int c) { return img->atXY(x, y, 0, c); })\
.addFunction("setXY", +[](format *img, int x, int y, int v) { return img->atXY(x, y) = v; })\
.addFunction("setXYC", +[](format *img, int x, int y, int c, int v) { return img->atXY(x, y, 0, c) = v; })\
.addFunction("conv", +[](format *img, const ImgDouble &kernel) { return img->convolve(kernel); })\
.addFunction("save",+[](format *img, const ImgDouble &kernel, const char *filename) { img->save(filename); })\
.endClass()

    BIND_IMG_FORMAT(ImgUInt8, "ImgUInt8", L);
    BIND_IMG_FORMAT(ImgDouble, "ImgDouble", L);
    BIND_IMG_FORMAT(ImgFloat, "ImgFloat", L);

#undef BIND_IMG_FORMAT
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    BindImgFormats(L);
    luaL_dofile(L, "initial.lua");
    luaL_dofile(L, "script.lua");
    return 0;
}