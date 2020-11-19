#pragma once

#include "RGBColor.h"
#include "ppm.h"
#include <string>

class Image
{
public:
	Image(std::string filepath);
	//returns the colour given the row/column coordinate for the ppm texture file
	virtual RGBColor get_color(int row, int column);

private:
	ppm* ppmObject;
};

