#include "MatteWave.h"

// ---------------------------------------------------------------- default constructor

MatteWave::MatteWave(void)
	: Material(),
	ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian)
{}



// ---------------------------------------------------------------- copy constructor

MatteWave::MatteWave(const MatteWave& m)
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
MatteWave::clone(void) const {
	return (new MatteWave(*this));
}


// ---------------------------------------------------------------- assignment operator

MatteWave&
MatteWave::operator= (const MatteWave& rhs) {
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

MatteWave::~MatteWave(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}


// ---------------------------------------------------------------- shade

RGBColor
MatteWave::shade(ShadeRec& sr) {
	Vector3D 	wo = -sr.ray.d;
	RGBColor 	L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights = sr.w.lights.size();

	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;

		if (ndotwi > 0.0)
			L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
	}

	return (L);
}


//caustics colour calculation
RGBColor MatteWave::shade_caustics(ShadeRec& sr, Vector3D& lightDir)
{
/*
	float strength = 0;

	lightDir = lightDir.hat();
	sr.normal.normalize();

	strength = dotProd(sr.normal, lightDir);

	strength = acos(strength) * (180.0 / PI);

	if (strength > 0.53)
		strength = 0;
*/

	float indexOfRefraction = 1.33;		//may need to change this to 1.33, testing it
	float strength = 0;

	Vector3D E = sr.ray.d;
	Vector3D N = sr.normal;
	lightDir = -lightDir;

	//find the transmission ray as outlined here:]
	//https://developer.download.nvidia.com/books/HTML/gpugems/gpugems_ch02.html

	double squareRoot = 1 + pow(indexOfRefraction, 2) * ((pow(dotProd(E, N), 2)) - 1);
	bool positive = true;
	if (squareRoot < 0)
		positive = false;
	squareRoot = abs(squareRoot);
	
	float mainBracket = (indexOfRefraction * dotProd(E, N));
	if (positive)
		mainBracket += squareRoot;
	else
		mainBracket -= squareRoot;

	Vector3D T = N * mainBracket + (indexOfRefraction * E);

	float angleBetweenTAndLight = acos(dotProd(lightDir, T)) * (180.0 / PI);

	float angleUpperLimit = 30;

	if (angleBetweenTAndLight >= 0 && angleBetweenTAndLight <= angleUpperLimit) {
		strength = (angleUpperLimit - angleBetweenTAndLight) / angleUpperLimit;
	}


	return RGBColor(white) * strength;// *0.53;
}




