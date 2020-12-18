#ifndef __IMAGE__
#define __IMAGE__


// 	Copyright (C) Kevin Suffern 2000-2007.
// 	Copyright (C) Stefan Brumme 2005.
// 	Copyright (C) Sverre Kvaale 2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This is not a texture
// The Image class stores an image in PPM format
// This is used for image based textures, including ramp textures such as marble and sandstone
// I originally chose the PPM format because it's simple to parse


#include <vector>		
#include "RGBColor.h"

#include "stb_image.h"
using namespace std;

//--------------------------------------------------------------------- class Image

class Image {	
	public:
	
		Image(void);	

		Image(const int h, const int v);

		Image(const Image& image);					

		Image& 										
		operator= (const Image& image);		

		//~Image(void) ;								
		
		void										
		read_ppm_file(const char* file_name);

		bool readTexture(const char* filePath);
		
		int
		get_hres(void);	
		
		int
		get_vres(void);	
				
		RGBColor									
		get_color(const int row, const int col) const;		
		
	private:
		int 				hres = 100;			// horizontal resolution of image
		int					vres = 100;			// vertical resolution of image
		vector<RGBColor> 	pixels;
		unsigned char* pixelData;		//needed by stb library
		int channel;					//also needed by stb
};


//--------------------------------------------------------------------- get_hres

inline int
Image::get_hres(void) {
	return (hres);
}


//--------------------------------------------------------------------- get_vres

inline int
Image::get_vres(void) {
	return (vres);
}

#endif
		
