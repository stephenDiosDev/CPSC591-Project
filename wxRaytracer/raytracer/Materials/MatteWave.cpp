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

	float strength = 0;

	lightDir = lightDir.hat();
	sr.normal.normalize();

	strength = dotProd(sr.normal, lightDir);

	strength = acos(strength);

	if (strength > 0.53)
		strength = 0;


/*	float indexOfRefraction = 1 / 1.33;		//may need to change this to 1.33, testing it
	Vector3D waveNormal = sr.normal;
	Vector3D incidentRay = sr.ray.d;
	bool positive = true;

	float squareRoot = 1 + (pow(indexOfRefraction, 2)) * ((pow(dotProd(incidentRay, waveNormal), 2)) - 1);
	if (squareRoot < 0) {	//preserve if it is negative or positive
		positive = false;
	}
	squareRoot = sqrt(abs(squareRoot));
	float brackets = 0;

	float leftHalf = (indexOfRefraction * dotProd(incidentRay, waveNormal));
	if (positive) {
		brackets = leftHalf + squareRoot;
	}
	else {
		brackets = leftHalf - squareRoot;
	}

	Vector3D transmissionRay = (waveNormal * brackets) + (indexOfRefraction * incidentRay);
	transmissionRay = transmissionRay * -1.0;

	//now we must find the angle between this ray and the sun
	//for now assume sun is straight up
	Vector3D sun(lightDir);

	float angleBetweenTransAndSun = dotProd(transmissionRay, sun) / ((transmissionRay.length()) * (sun.length()));
	angleBetweenTransAndSun = acos(angleBetweenTransAndSun);	//angle in degrees

	float angleLimit = 0.53;
	float strength = 0;		//0 = no strength, 1 = max strength
	if (angleBetweenTransAndSun >= 0 && angleBetweenTransAndSun <= 90) {	//no angles outside of this range should be considered
		strength = (90 - angleBetweenTransAndSun) / 90;
	}
*/
	return RGBColor(white) * strength;
}




