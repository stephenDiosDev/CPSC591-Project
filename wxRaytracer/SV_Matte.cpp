#include "SV_Matte.h"
// ---------------------------------------------------------------- default constructor

SV_Matte::SV_Matte(void)
	: Material(),
	ambient_brdf(new SV_Lambertian),
	diffuse_brdf(new SV_Lambertian)
{}



// ---------------------------------------------------------------- copy constructor

SV_Matte::SV_Matte(const SV_Matte& m)
	: Material(m)
{
	if (m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone();
	else  ambient_brdf = NULL;

	if (m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone();
	else  diffuse_brdf = NULL;
}


// ---------------------------------------------------------------- clone

Material*
SV_Matte::clone(void) const {
	return (new SV_Matte(*this));
}


// ---------------------------------------------------------------- assignment operator

SV_Matte&
SV_Matte::operator= (const SV_Matte& rhs) {
	if (this == &rhs)
		return (*this);

	Material::operator=(rhs);

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- destructor

SV_Matte::~SV_Matte(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}
