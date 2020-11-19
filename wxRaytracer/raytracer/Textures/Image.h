#pragma once

#include "RGBColor.h"

class Image
{
public:
	//returns the colour given the row/column coordinate for the ppm texture file
	virtual RGBColor get_color(int row, int column);
};

