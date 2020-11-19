#include "ImageTexture.h"


RGBColor ImageTexture::get_color(const ShadeRec& sr) const
{
	int row, column;

	row = (int)(sr.v * (vres - 1));
	column = (int)(sr.u * (hres - 1));

	return (image_ptr->get_color(row, column));
}
