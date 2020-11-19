#pragma once

#include "ShadeRec.h"
#include "RGBColor.h"
#include "Image.h"
#include "ppm.h"

class ImageTexture
{
public:
	ImageTexture(Image* imgptr);

	virtual RGBColor get_color(const ShadeRec& sr) const;

private:
	int hres;	//image horizontal resolution
	int vres;	//image vertical resolution
	Image* image_ptr;
};

