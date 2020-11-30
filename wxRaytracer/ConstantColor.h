#pragma once
#include "Texture.h"
class ConstantColor :
    public Texture
{
    	public:
			ConstantColor(void);

			ConstantColor(const ConstantColor& constantColor);

			virtual ConstantColor*
				clone(void) const = 0;

			virtual
				~ConstantColor(void);
		
		void
		set_color(const RGBColor& c); 
		
		virtual RGBColor														
		get_color(const ShadeRec& sr) const;
		
	private:
		
		RGBColor* color;	 // the color		
};
		
		
RGBColor
ConstantColor::get_color(const ShadeRec& sr) const {
	return (*color);
};

