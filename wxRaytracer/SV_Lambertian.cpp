#include "SV_Lambertian.h"
// ---------------------------------------------------------------------- default constructor

SV_Lambertian::SV_Lambertian(void)
	: BRDF(),
	kd(0.0),
	cd()
{}


// ---------------------------------------------------------------------- copy constructor

SV_Lambertian::SV_Lambertian(const SV_Lambertian& lamb)
	: BRDF(lamb),
	kd(lamb.kd),
	cd(lamb.cd)
{}


// ---------------------------------------------------------------------- clone

SV_Lambertian*
SV_Lambertian::clone(void) const {
	return (new SV_Lambertian(*this));
}


// ---------------------------------------------------------------------- destructor

SV_Lambertian::~SV_Lambertian(void) {}


// ---------------------------------------------------------------------- assignment operator

SV_Lambertian&
SV_Lambertian::operator= (const SV_Lambertian& rhs) {
	if (this == &rhs)
		return (*this);

	BRDF::operator= (rhs);

	kd = rhs.kd;
	cd = rhs.cd;

	return (*this);
}
