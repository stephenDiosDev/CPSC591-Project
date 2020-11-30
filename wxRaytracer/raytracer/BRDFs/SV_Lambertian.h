#pragma once
#include "BRDF.h"
#include "Texture.h"
#include "Constants.h"
class SV_Lambertian : public BRDF {
public:
	//may need to delete the .h constructors here, same with ConstantColor so it uses the parents
	SV_Lambertian(void);

	SV_Lambertian(const SV_Lambertian& lamb);

	virtual SV_Lambertian*
		clone(void) const;

	~SV_Lambertian(void);

	SV_Lambertian&
		operator= (const SV_Lambertian& rhs);

	virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;

	virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	void
		set_ka(const float ka);

	void
		set_kd(const float kd);

	void set_cd(const Texture* t_ptr);

private:

	float		kd;
	Texture* cd;
};

inline
RGBColor
SV_Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (kd * cd->get_color(sr));
}

inline
RGBColor
SV_Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (kd * cd->get_color(sr) * invPI);
}

// -------------------------------------------------------------- set_ka

inline void
SV_Lambertian::set_ka(const float k) {
	kd = k;
}



// -------------------------------------------------------------- set_kd

inline void
SV_Lambertian::set_kd(const float k) {
	kd = k;
}

inline
void SV_Lambertian::set_cd(const Texture* t_ptr) {
	cd = t_ptr->clone();
}

