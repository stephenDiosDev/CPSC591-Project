#include "Directional.h"

// ---------------------------------------------------------------------- default constructor

Directional::Directional(void)
	: 	Light(),
		ls(1.0),
		color(1.0),
		dir(0, 1, 0)			
{}


// ---------------------------------------------------------------------- dopy constructor

Directional::Directional(const Directional& dl)
	: 	Light(dl),
		ls(dl.ls),
		color(dl.color),
		dir(dl.dir)  		
{}


// ---------------------------------------------------------------------- clone

Light* 
Directional::clone(void) const {
	return (new Directional(*this));
}


// ---------------------------------------------------------------------- assignment operator

Directional& 
Directional::operator= (const Directional& rhs) 	
{
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls		= rhs.ls;
	color 	= rhs.color;
	dir 	= rhs.dir;

	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

Directional::~Directional(void) {}


// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined 

Vector3D								
Directional::get_direction(ShadeRec& sr) {
	return (dir);
}	

// ------------------------------------------------------------------------------  L

RGBColor
Directional::L(ShadeRec& s) {	
	return (ls * color);
}

bool Directional::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	float t;
	int numObjects = sr.w.objects.size();
	//float d = sr.hit_point.distance(ray.o);

	for (int j = 0; j < numObjects; j++) {	//need to make sure we dont hit the wave and cause shadow
		if (sr.w.objects[j]->shadow_hit(ray, t))// && t < d)
		{
			return (true);
		}
			
	}

	return (false);
}


