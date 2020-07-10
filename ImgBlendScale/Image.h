#pragma once
//*********************************************
//Image class to hold and allow manipulation of images once read into the code
//from https://www.scratchapixel.com/
//*********************************************
#include <cstdlib> 
#include <cstdio> 

class Image
{
public:
	// Rgb structure, i.e. a pixel 
	struct Rgb
	{
		Rgb() : r(0), g(0), b(0) {}
		Rgb(float c) : r(c), g(c), b(c) {}
		Rgb(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
		bool operator != (const Rgb &c) const
		{
			return c.r != r || c.g != g || c.b != b;
		}
		Rgb& operator *= (const Rgb &rgb)
		{
			r *= rgb.r, g *= rgb.g, b *= rgb.b; return *this;
		}
		Rgb& operator += (const Rgb &rgb)
		{
			r += rgb.r, g += rgb.g, b += rgb.b; return *this;
		}
		friend float& operator += (float &f, const Rgb rgb)
		{
			f += (rgb.r + rgb.g + rgb.b) / 3.f; return f;
		}
		float r, g, b;
	};

	Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }
	Image(const unsigned int &_w, const unsigned int &_h, const Rgb &c = kBlack) :
		w(_w), h(_h), pixels(NULL)
	{
		pixels = new Rgb[w * h];
		for (int i = 0; i < w * h; ++i)
			pixels[i] = c;
	}
	const Rgb& operator [] (const unsigned int &i) const
	{
		return pixels[i];
	}
	Rgb& operator [] (const unsigned int &i)
	{
		return pixels[i];
	}
	~Image()
	{
		//if (pixels != NULL) delete[] pixels;
		//delete[] pixels;
	}
	unsigned int w, h; // Image resolution 
	Rgb *pixels; // 1D array of pixels 
	static const Rgb kBlack, kWhite, kRed, kGreen, kBlue; // Preset colors










	//COPY CONSTRUCTOR & ASSIGNMENT OPERATOR
	/*Image (const Image &im)
	{
		w = im.w;
		h = im.h;
		pixels = new Rgb[im.w * im.h];
		for (int i = 0; i < im.w * im.h; ++i)
		{
			pixels[i] = im.pixels[i];
		}
	}

	Image& operator = (const Image& other)
	{
		w = other.w;
		h = other.h;
		pixels = new Rgb[other.w * other.h];
		for (int i = 0; i < other.w * other.h; ++i)
		{
			pixels[i] = other.pixels[i];
		}
		return *this;
	}*/










	//IMAGE INFORMATION
	void printImgInfo(const char *filename)
	{
		std::ifstream ifs;
		ifs.open(filename, std::ios::binary);
		std::string filetype;
		int w, h, b;
		ifs >> filetype;
		ifs >> w >> h >> b;
		std::cout << filename << std::endl;
		std::cout << filetype << " (Portable Pixmap Format)" << std::endl;
		std::cout << w << " x " << h << std::endl;
		std::cout << b << " (Colour Depth)\n" << std::endl;
		
	}
	
	void printImgInfo(const Image &imageName, bool upscaled)
	{
	 	switch (imageName.w)
		{
			case 1500: std::cout << "Upscaled2X.ppm" << std::endl; break;
			case 3000: std::cout << "Upscaled4X.ppm" << std::endl; break;
			case 4592: std::cout << "Please use const char *filename argument for the blended images." << std::endl; break;
		}
		std::cout << "P6 (Portable Pixmap Format)" << std::endl;
		std::cout << imageName.w << " x " << imageName.h << std::endl;
		if (upscaled == true)
		{
			std::cout << "Original Dimensions: 750 x 750" << std::endl;
			switch (imageName.w)
			{
				case 1500: std::cout << "Image Upscaled: 2X" << std::endl; break;
				case 3000: std::cout << "Image Upscaled: 4X" << std::endl; break;
				case 4592: std::cout << "Please use const char *filename argument for the blended images." << std::endl; break;
			}
		}
		std::cout << "255 (Colour Depth)\n" << std::endl;
	}
	//----------
};










//IMAGE UPSCALE
class ImageZoom: public Image
{
	private:
	int zoomW, zoomH;
	public:
	Image upscaler(Image preDef, int wh)
	{
		zoomW = wh; zoomH = wh;
		Image *upscaledImg = new Image(zoomW, zoomH);
		double xRatio = preDef.w / (double)zoomW;
		double yRatio = preDef.h / (double)zoomH;
		double px, py;
		for (int i = 0; i < zoomH; i++)
		{
			for (int j = 0; j < zoomW; j++)
			{
				px = floor(j * xRatio);
				py = floor(i * yRatio);
				upscaledImg->pixels[(i * zoomW) + j] = preDef.pixels[(int)((py * preDef.w) + px)];
			}
		}
		return *upscaledImg;
	}

	Image upscaler(Image preDef, int w, int h)
	{
		zoomW = w; zoomH = h;
		Image *upscaledImg = new Image(zoomW, zoomH);
		double xRatio = preDef.w / (double)zoomW;
		double yRatio = preDef.h / (double)zoomH;
		double px, py;
		for (int i = 0; i < zoomH; i++)
		{
			for (int j = 0; j < zoomW; j++)
			{
				px = floor(j * xRatio);
				py = floor(i * yRatio);
				upscaledImg->pixels[(i * zoomW) + j] = preDef.pixels[(int)((py * preDef.w) + px)];
			}
		}
		return *upscaledImg;
	}
};
//----------

const Image::Rgb Image::kBlack = Image::Rgb(0);
const Image::Rgb Image::kWhite = Image::Rgb(1);
const Image::Rgb Image::kRed = Image::Rgb(1, 0, 0);
const Image::Rgb Image::kGreen = Image::Rgb(0, 1, 0);
const Image::Rgb Image::kBlue = Image::Rgb(0, 0, 1);
