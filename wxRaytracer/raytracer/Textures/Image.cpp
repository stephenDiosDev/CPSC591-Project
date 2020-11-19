#include "Image.h"

Image::Image(std::string filepath) {
	//populate ppm object and read in ppm stuff
	ppmObject->read(filepath);
}

RGBColor Image::get_color(int row, int column) {
	int index = (ppmObject->width * row) + column;
	RGBColor result(ppmObject->r[index], ppmObject->g[index], ppmObject->b[index]);
	return result;
}