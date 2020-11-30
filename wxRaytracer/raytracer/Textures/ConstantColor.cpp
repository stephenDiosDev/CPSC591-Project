#include "ConstantColor.h"
// ---------------------------------------------------------------- default constructor

ConstantColor::ConstantColor(void) {}


// ---------------------------------------------------------------- copy constructor

ConstantColor::ConstantColor(const ConstantColor& texture) {}


ConstantColor*
ConstantColor::clone(void) const {
	return (new ConstantColor(*this));
}


// ---------------------------------------------------------------- assignment operator

ConstantColor&
ConstantColor::operator= (const ConstantColor& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------- destructor

ConstantColor::~ConstantColor(void) {}

void ConstantColor::set_color(const RGBColor& c)
{
	*color = c;
}
