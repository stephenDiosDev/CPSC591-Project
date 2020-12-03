#ifndef __MATTEWAVE__
#define __MATTEWAVE__

#include "Material.h"
#include "Lambertian.h"

//----------------------------------------------------------------------------- class Matte

class MatteWave : public Material {
public:

	MatteWave(void);

	MatteWave(const MatteWave& m);

	virtual Material*
		clone(void) const;

	MatteWave&
		operator= (const MatteWave& rhs);

	~MatteWave(void);

	void
		set_ka(const float k);

	void
		set_kd(const float k);

	void
		set_cd(const RGBColor c);

	void
		set_cd(const float r, const float g, const float b);

	void
		set_cd(const float c);

	virtual RGBColor
		shade(ShadeRec& sr);

private:

	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
};


// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void
MatteWave::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void
MatteWave::set_kd(const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void
MatteWave::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// ---------------------------------------------------------------- set_cd

inline void
MatteWave::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void
MatteWave::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

#endif

