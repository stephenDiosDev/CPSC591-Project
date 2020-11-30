#pragma once
#include "Texture.h"
class ConstantColor :
    public Texture
{
    	public:
			ConstantColor(void);

			ConstantColor(const ConstantColor& constantColor);

			virtual ConstantColor*
				clone(void) const;

			virtual
				~ConstantColor(void);

			ConstantColor&
				ConstantColor::operator= (const ConstantColor& rhs);
		
		void
		set_color(const RGBColor& c); 
		
		virtual RGBColor														
		get_color(const ShadeRec& sr) const;
		
	private:
		
		RGBColor* color = new RGBColor(1.0, 1.0, 1.0);	 // the color		
};
		
inline
RGBColor
ConstantColor::get_color(const ShadeRec& sr) const {
	return (*color);
};

