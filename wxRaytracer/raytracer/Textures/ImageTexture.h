#pragma once

#include "Texture.h"
#include "Image.h"

class ImageTexture : Texture
{
public:
	virtual RGBColor get_color(const ShadeRec& sr) const;

private:
	int hres;	//image horizontal resolution
	int vres;	//image vertical resolution
	Image* image_ptr;	//image variable to store the PPM file
};

