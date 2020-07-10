#pragma once
#include <cstdlib> 
#include <cstdio> 
#include "Image.h"

int imgSize = 4592 * 3056;

class Blending
{
public:
    int itrtrConfig;
    void meanInitial(Image *img1, Image *img2, Image *img3, Image *img4, Image *img5, Image *img6, Image *img7, Image *img8, Image *img9, Image *img10/*, Image *img11, Image *img12, Image *img13*/);
    void meanCompiler(Image *preDef);
    void medianInitial(Image *img1, Image *img2, Image *img3, Image *img4, Image *img5, Image *img6, Image *img7, Image *img8, Image *img9, Image *img10/*, Image *img11, Image *img12, Image *img13*/);
    void standardDeviation(Image *img1, Image *img2, Image *img3, Image *img4, Image *img5, Image *img6, Image *img7, Image *img8, Image *img9, Image *img10/*, Image *img11, Image *img12, Image *img13*/);
private:
    Image stdDevP2(Image *tempImage);
    void clipper(int itrtr, Image *img1, Image *img2, Image *img3, Image *img4, Image *img5, Image *img6, Image *img7, Image *img8, Image *img9, Image *img10/*, Image *img11, Image *img12, Image *img13*/);
    Image clippedMean(Image *preDef, Image *topClip, Image *bottomClip);
};