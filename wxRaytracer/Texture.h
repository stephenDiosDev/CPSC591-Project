#pragma once

#include "RGBColor.h"
#include "ShadeRec.h"

class Texture
{
public:
	//constructors

	virtual RGBColor get_color(const ShadeRec& sr) const = 0;
};

