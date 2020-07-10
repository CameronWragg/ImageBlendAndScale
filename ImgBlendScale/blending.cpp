#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include "Blending.h"
#include "Readwrite.h"

Readwrite rw;
Blending blend;
Image *sigmaClipImg = new Image(4592, 3056);
Image *meanImg = new Image(4592, 3056);
Image *medianImg = new Image(4592, 3056);
Image *stdDevP3 = new Image(4592, 3056);
Image *stdDevFinal = new Image(4592, 3056);
float divNo[4592 * 3056];
Image *clp1 = new Image(4592,3056);
Image *clp2 = new Image(4592,3056);
Image *clp3 = new Image(4592,3056);
Image *clp4 = new Image(4592,3056);
Image *clp5 = new Image(4592,3056);
Image *clp6 = new Image(4592,3056);
Image *clp7 = new Image(4592,3056);
Image *clp8 = new Image(4592,3056);
Image *clp9 = new Image(4592,3056);
Image *clp10 = new Image(4592,3056);
/*Image *clp11 = new Image(4592,3056);
Image *clp12 = new Image(4592,3056);
Image *clp13 = new Image(4592,3056);*/
int itrtr = 0;

//MEAN BLEND
void Blending::meanInitial(Image *img1, Image *img2, Image *img3, Image *img4, Image *img5, Image *img6, Image *img7, Image *img8, Image *img9, Image *img10/*, Image *img11, Image *img12, Image *img13*/)
{
	if (itrtr != 0)
	{
		for (int cPxl = 0; cPxl < imgSize; cPxl++)
		{
			meanImg->pixels[cPxl].r = 0;
			meanImg->pixels[cPxl].g = 0;
			meanImg->pixels[cPxl].b = 0;
		}
	}
		for (int i = 0; i < 10; i++)
		{
			switch (i)
			{
			case 0:
				blend.meanCompiler(img1);
				break;
			case 1:
				blend.meanCompiler(img2);
				break;
			case 2:
				blend.meanCompiler(img3);
				break;
			case 3:
				blend.meanCompiler(img4);
				break;
			case 4:
				blend.meanCompiler(img5);
				break;
			case 5:
				blend.meanCompiler(img6);
				break;
			case 6:
				blend.meanCompiler(img7);
				break;
			case 7:
				blend.meanCompiler(img8);
				break;
			case 8:
				blend.meanCompiler(img9);
				break;
			case 9:
				blend.meanCompiler(img10);
				break;
			/*case 10:
				blend.meanCompiler(img11);
				break;
			case 11:
				blend.meanCompiler(img12);
				break;
			case 12:
				blend.meanCompiler(img13);
				break;*/
			}
		}
	if (itrtr == 0)
	{
		for (int cPxl = 0; cPxl < imgSize; cPxl++)
		{
			meanImg->pixels[cPxl].r /= 10;
			meanImg->pixels[cPxl].g /= 10;
			meanImg->pixels[cPxl].b /= 10;
		}
		std::cout << "\nWriting Mean Blended Image." << std::endl;
		rw.writePPM(*meanImg, "meanFinal.ppm");
	}
	else
	{
		for (int cPxl = 0; cPxl < imgSize; cPxl++)
		{
			meanImg->pixels[cPxl].r /= divNo[cPxl];
			meanImg->pixels[cPxl].g /= divNo[cPxl];
			meanImg->pixels[cPxl].b /= divNo[cPxl];
		}
	}
}

void Blending::meanCompiler(Image *preDef)
{
	for (int cPxl = 0; cPxl < imgSize; cPxl++)
	{
		meanImg->pixels[cPxl].r += preDef->pixels[cPxl].r;
		meanImg->pixels[cPxl].g += preDef->pixels[cPxl].g;
		meanImg->pixels[cPxl].b += preDef->pixels[cPxl].b;
	}
}
//----------










//MEDIAN BLEND
void Blending::medianInitial(Image *img1, Image *img2, Image *img3, Image *img4, Image *img5, Image *img6, Image *img7, Image *img8, Image *img9, Image *img10/*, Image *img11, Image *img12, Image *img13*/)
{
	Image *tempImage = new Image(4592, 3056);

	float cPxlR[10];
	float cPxlG[10];
	float cPxlB[10];

		for (int cPxl = 0; cPxl < imgSize; cPxl++)
		{
			for (int cImg = 0; cImg < 10; cImg++)
			{
				switch (cImg)
				{
					case 0: *tempImage = *img1;
					break;
					case 1: *tempImage = *img2;
					break;
					case 2: *tempImage = *img3;
					break;
					case 3: *tempImage = *img4;
					break;
					case 4: *tempImage = *img5;
					break;
					case 5: *tempImage = *img6;
					break;
					case 6: *tempImage = *img7;
					break;
					case 7: *tempImage = *img8;
					break;
					case 8: *tempImage = *img9;
					break;
					case 9: *tempImage = *img10;
					break;
					/*case 10: *tempImage = *img11;
					break;
					case 11: *tempImage = *img12;
					break;
					case 12: *tempImage = *img13;
					break;*/
				}
				cPxlR[cImg] = tempImage->pixels[cPxl].r;
				cPxlG[cImg] = tempImage->pixels[cPxl].g;
				cPxlB[cImg] = tempImage->pixels[cPxl].b;
			}
			std::sort(std::begin(cPxlR), std::end(cPxlR));
			std::sort(std::begin(cPxlG), std::end(cPxlG));
			std::sort(std::begin(cPxlB), std::end(cPxlB));
			if (itrtr == 0 || divNo[cPxl] == 10)
			{
				medianImg->pixels[cPxl].r = (cPxlR[5] + cPxlR[6]) / 2;
				medianImg->pixels[cPxl].g = (cPxlG[5] + cPxlG[6]) / 2;
				medianImg->pixels[cPxl].b = (cPxlB[5] + cPxlB[6]) / 2;
			}
			else if (divNo[cPxl] != 10 || divNo[cPxl] != 8 || divNo[cPxl] != 6 || divNo[cPxl] != 4 || divNo[cPxl] != 2)
			{
				int nuMed;
				if (divNo[cPxl] == 9){nuMed = 5;}
				else if (divNo[cPxl] == 7){nuMed = 4;}
				else if (divNo[cPxl] == 5){nuMed = 3;}
				else if (divNo[cPxl] == 3){nuMed = 2;}
				else if (divNo[cPxl] == 1){nuMed = 1;}
				medianImg->pixels[cPxl].r = cPxlR[nuMed];
				medianImg->pixels[cPxl].g = cPxlR[nuMed];
				medianImg->pixels[cPxl].b = cPxlR[nuMed];
			}
			else
			{
				if (divNo[cPxl] == 8)
				{
					medianImg->pixels[cPxl].r = (cPxlR[4] + cPxlR[5]) / 2;
					medianImg->pixels[cPxl].g = (cPxlG[4] + cPxlG[5]) / 2;
					medianImg->pixels[cPxl].b = (cPxlB[4] + cPxlB[5]) / 2;
				}
				if (divNo[cPxl] == 6)
				{
					medianImg->pixels[cPxl].r = (cPxlR[3] + cPxlR[4]) / 2;
					medianImg->pixels[cPxl].g = (cPxlG[3] + cPxlG[4]) / 2;
					medianImg->pixels[cPxl].b = (cPxlB[3] + cPxlB[4]) / 2;
				}
				if (divNo[cPxl] == 4)
				{
					medianImg->pixels[cPxl].r = (cPxlR[2] + cPxlR[3]) / 2;
					medianImg->pixels[cPxl].g = (cPxlG[2] + cPxlG[3]) / 2;
					medianImg->pixels[cPxl].b = (cPxlB[2] + cPxlB[3]) / 2;
				}
				if (divNo[cPxl] == 2)
				{
					medianImg->pixels[cPxl].r = (cPxlR[1] + cPxlR[2]) / 2;
					medianImg->pixels[cPxl].g = (cPxlG[1] + cPxlG[2]) / 2;
					medianImg->pixels[cPxl].b = (cPxlB[1] + cPxlB[2]) / 2;
				}
			}
		}
		if (itrtr == 0)
		{
			std::cout << "Writing Median Blended Image." << std::endl;
			rw.writePPM(*medianImg, "medianFinal.ppm");
		}
}
//----------










//STANDARD DEVIATION
void Blending::standardDeviation(Image *img1, Image *img2, Image *img3, Image *img4, Image *img5, Image *img6, Image *img7, Image *img8, Image *img9, Image *img10/*, Image *img11, Image *img12, Image *img13*/)
{
	*img1 = rw.readPPM("Images/ImageStacker_set3/IMG_1.ppm");
	clp1 = img1;
	*img2 = rw.readPPM("Images/ImageStacker_set3/IMG_2.ppm");
	clp2 = img2;
	*img3 = rw.readPPM("Images/ImageStacker_set3/IMG_3.ppm");
	clp3 = img3;
	*img4 = rw.readPPM("Images/ImageStacker_set3/IMG_4.ppm");
	clp4 = img4;
	*img5 = rw.readPPM("Images/ImageStacker_set3/IMG_5.ppm");
	clp5 = img5;
	*img6 = rw.readPPM("Images/ImageStacker_set3/IMG_6.ppm");
	clp6 = img6;
	*img7 = rw.readPPM("Images/ImageStacker_set3/IMG_7.ppm");
	clp7 = img7;
	*img8 = rw.readPPM("Images/ImageStacker_set3/IMG_8.ppm");
	clp8 = img8;
	*img9 = rw.readPPM("Images/ImageStacker_set3/IMG_9.ppm");
	clp9 = img9;
	*img10 = rw.readPPM("Images/ImageStacker_set3/IMG_10.ppm");
	clp10 = img10;
	/**img11 = rw.readPPM("Images/ImageStacker_set3/IMG_11.ppm");
	clp11 = img11;
	*img12 = rw.readPPM("Images/ImageStacker_set3/IMG_12.ppm");
	clp12 = img12;
	*img13 = rw.readPPM("Images/ImageStacker_set3/IMG_13.ppm");
	clp13 = img13;*/
	std::cout << "10 Images Refreshed." << std::endl;
	Image *tempImage = new Image(4592, 3056);
	
for (itrtr = 0; itrtr < 1; itrtr++)
{
	for (int cPxl = 0; cPxl < imgSize; cPxl++)
	{
		divNo[cPxl] = 10;
	}
	for (int cImg = 0; cImg < 10; cImg++)
	{
		if (itrtr == 0)
		{
			switch(cImg)
			{
				case 0: *tempImage = *img1; *img1 = blend.stdDevP2(tempImage);
				break;
				case 1: *tempImage = *img2; *img2 = blend.stdDevP2(tempImage);
				break;
				case 2: *tempImage = *img3; *img3 = blend.stdDevP2(tempImage);
				break;
				case 3: *tempImage = *img4; *img4 = blend.stdDevP2(tempImage);
				break;
				case 4: *tempImage = *img5; *img5 = blend.stdDevP2(tempImage);
				break;
				case 5: *tempImage = *img6; *img6 = blend.stdDevP2(tempImage);
				break;
				case 6: *tempImage = *img7; *img7 = blend.stdDevP2(tempImage);
				break;
				case 7: *tempImage = *img8; *img8 = blend.stdDevP2(tempImage);
				break;
				case 8: *tempImage = *img9; *img9 = blend.stdDevP2(tempImage);
				break;
				case 9: *tempImage = *img10; *img10 = blend.stdDevP2(tempImage);
				break;
				/*case 10: *tempImage = *img11; *img11 = blend.stdDevP2(tempImage);
				break;
				case 11: *tempImage = *img12; *img12 = blend.stdDevP2(tempImage);
				break;
				case 12: *tempImage = *img13; *img13 = blend.stdDevP2(tempImage);
				break;*/
			}
		}
		else
		{
			switch(cImg)
			{
				case 0: *tempImage = *clp1; *img1 = blend.stdDevP2(tempImage);
				break;
				case 1: *tempImage = *clp2; *img2 = blend.stdDevP2(tempImage);
				break;
				case 2: *tempImage = *clp3; *img3 = blend.stdDevP2(tempImage);
				break;
				case 3: *tempImage = *clp4; *img4 = blend.stdDevP2(tempImage);
				break;
				case 4: *tempImage = *clp5; *img5 = blend.stdDevP2(tempImage);
				break;
				case 5: *tempImage = *clp6; *img6 = blend.stdDevP2(tempImage);
				break;
				case 6: *tempImage = *clp7; *img7 = blend.stdDevP2(tempImage);
				break;
				case 7: *tempImage = *clp8; *img8 = blend.stdDevP2(tempImage);
				break;
				case 8: *tempImage = *clp9; *img9 = blend.stdDevP2(tempImage);
				break;
				case 9: *tempImage = *clp10; *img10 = blend.stdDevP2(tempImage);
				break;
				/*case 10: *tempImage = *clp11; *img11 = blend.stdDevP2(tempImage);
				break;
				case 11: *tempImage = *clp12; *img12 = blend.stdDevP2(tempImage);
				break;
				case 12: *tempImage = *clp13; *img13 = blend.stdDevP2(tempImage);
				break;*/
			}
		}
	}
	itrtr++;
	meanInitial(img1, img2, img3, img4, img5, img6, img7, img8, img9, img10/*, img11, img12, img13*/);
	itrtr--;
	for (int cPxl = 0; cPxl < imgSize; cPxl++)
	{
		stdDevFinal->pixels[cPxl].r = sqrt (meanImg->pixels[cPxl].r);
		stdDevFinal->pixels[cPxl].g = sqrt (meanImg->pixels[cPxl].g);
		stdDevFinal->pixels[cPxl].b = sqrt (meanImg->pixels[cPxl].b);
	}
	std::cout << "Standard Deviation Obtained." << std::endl;
	blend.clipper(itrtr, img1, img2, img3, img4, img5, img6, img7, img8, img9, img10/*, img11, img12, img13*/);
}
	std::cout << "Writing Sigma Clipped Mean Blended Image" << std::endl;
	rw.writePPM(*sigmaClipImg, "sigmaClippedFinal.ppm");
}

Image Blending::stdDevP2(Image *preDef)
{
	for (int cPxl = 0; cPxl < imgSize; cPxl++)
	{
		preDef->pixels[cPxl].r -= meanImg->pixels[cPxl].r;
		preDef->pixels[cPxl].g -= meanImg->pixels[cPxl].g;
		preDef->pixels[cPxl].b -= meanImg->pixels[cPxl].b;
	}
	for (int cPxl = 0; cPxl < imgSize; cPxl++)
	{
		preDef->pixels[cPxl].r = pow (preDef->pixels[cPxl].r, 2);
		preDef->pixels[cPxl].g = pow (preDef->pixels[cPxl].g, 2);
		preDef->pixels[cPxl].b = pow (preDef->pixels[cPxl].b, 2);
	}
	return *preDef;
}
//----------










//SIGMA CLIPPED MEAN
void Blending::clipper(int itrtr, Image *img1, Image *img2, Image *img3, Image *img4, Image *img5, Image *img6, Image *img7, Image *img8, Image *img9, Image *img10/*, Image *img11, Image *img12, Image *img13*/)
{
	Image *topClip = new Image(4592, 3056);
	Image *bottomClip = new Image(4592, 3056);

	if (itrtr != 0)
	{
		medianInitial(img1, img2, img3, img4, img5, img6, img7, img8, img9, img10/*, img11, img12, img13*/);
	}
	for (int cPxl = 0; cPxl < imgSize; cPxl++)
	{
		topClip->pixels[cPxl].r = medianImg->pixels[cPxl].r + (stdDevFinal->pixels[cPxl].r * 1.5);
		topClip->pixels[cPxl].g = medianImg->pixels[cPxl].g + (stdDevFinal->pixels[cPxl].g * 1.5);
		topClip->pixels[cPxl].b = medianImg->pixels[cPxl].b + (stdDevFinal->pixels[cPxl].b * 1.5);

		bottomClip->pixels[cPxl].r = medianImg->pixels[cPxl].r - (stdDevFinal->pixels[cPxl].r * 1.5);
		bottomClip->pixels[cPxl].g = medianImg->pixels[cPxl].g - (stdDevFinal->pixels[cPxl].g * 1.5);
		bottomClip->pixels[cPxl].b = medianImg->pixels[cPxl].b - (stdDevFinal->pixels[cPxl].b * 1.5);
	}
	std::cout << "Top & Bottom boundaries defined." << std::endl;
	
	*img1 = rw.readPPM("Images/ImageStacker_set3/IMG_1.ppm");
	*img2 = rw.readPPM("Images/ImageStacker_set3/IMG_2.ppm");
	*img3 = rw.readPPM("Images/ImageStacker_set3/IMG_3.ppm");
	*img4 = rw.readPPM("Images/ImageStacker_set3/IMG_4.ppm");
	*img5 = rw.readPPM("Images/ImageStacker_set3/IMG_5.ppm");
	*img6 = rw.readPPM("Images/ImageStacker_set3/IMG_6.ppm");
	*img7 = rw.readPPM("Images/ImageStacker_set3/IMG_7.ppm");
	*img8 = rw.readPPM("Images/ImageStacker_set3/IMG_8.ppm");
	*img9 = rw.readPPM("Images/ImageStacker_set3/IMG_9.ppm");
	*img10 = rw.readPPM("Images/ImageStacker_set3/IMG_10.ppm");
	/**img11 = rw.readPPM("Images/ImageStacker_set3/IMG_11.ppm");
	*img12 = rw.readPPM("Images/ImageStacker_set3/IMG_12.ppm");
	*img13 = rw.readPPM("Images/ImageStacker_set3/IMG_13.ppm");*/
	std::cout << "10 Images Refreshed." << std::endl;

		for (int i = 0; i < 10; i++)
		{
			switch (i)
			{
			case 0:
				*clp1 = blend.clippedMean(img1, topClip, bottomClip);
				break;
			case 1: 
				*clp2 = blend.clippedMean(img2, topClip, bottomClip);
				break;
			case 2:
				*clp3 = blend.clippedMean(img3, topClip, bottomClip);
				break;
			case 3: 
				*clp4 = blend.clippedMean(img4, topClip, bottomClip);
				break;
			case 4: 
				*clp5 = blend.clippedMean(img5, topClip, bottomClip);
				break;
			case 5: 
				*clp6 = blend.clippedMean(img6, topClip, bottomClip);
				break;
			case 6: 
				*clp7 = blend.clippedMean(img7, topClip, bottomClip);
				break;
			case 7: 
				*clp8 = blend.clippedMean(img8, topClip, bottomClip);
				break;
			case 8: 
				*clp9 = blend.clippedMean(img9, topClip, bottomClip);
				break;
			case 9: 
				*clp10 = blend.clippedMean(img10, topClip, bottomClip);
				break;
			/*case 10:
				*clp11 = blend.clippedMean(img11, topClip, bottomClip);
				break;
			case 11:
				*clp12 = blend.clippedMean(img12, topClip, bottomClip);
				break;
			case 12:
				*clp13 = blend.clippedMean(img13, topClip, bottomClip);
				break;*/
			}
		}
		std::cout << "Clipped 10 Images. (Iteration: " << (itrtr + 1) << ")" << std::endl;
	for (int cPxl = 0; cPxl < imgSize; cPxl++)
	{
		sigmaClipImg->pixels[cPxl].r /= divNo[cPxl];
		sigmaClipImg->pixels[cPxl].g /= divNo[cPxl];
		sigmaClipImg->pixels[cPxl].b /= divNo[cPxl];
	}
}

Image Blending::clippedMean(Image *preDef, Image *topClip, Image *bottomClip)
{
	for (int cPxl = 0; cPxl < imgSize; cPxl++)
	{
		if (bottomClip->pixels[cPxl].r <= preDef->pixels[cPxl].r && topClip->pixels[cPxl].r >= preDef->pixels[cPxl].r 
		&& bottomClip->pixels[cPxl].g <= preDef->pixels[cPxl].g && topClip->pixels[cPxl].g >= preDef->pixels[cPxl].g 
		&& bottomClip->pixels[cPxl].b <= preDef->pixels[cPxl].b && topClip->pixels[cPxl].b >= preDef->pixels[cPxl].b)
		{
			sigmaClipImg->pixels[cPxl].r += preDef->pixels[cPxl].r;
			sigmaClipImg->pixels[cPxl].g += preDef->pixels[cPxl].g;
			sigmaClipImg->pixels[cPxl].b += preDef->pixels[cPxl].b;
		}
		else
		{
			divNo[cPxl] -= 1;
		}
	}
	return *preDef;
}
//----------