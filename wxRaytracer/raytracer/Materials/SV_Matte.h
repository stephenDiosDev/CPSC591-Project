#define __SVMATTE__

#include "Material.h"
#include "SV_Lambertian.h"
class SV_Matte : public Material {
public:
	SV_Matte(void);

	SV_Matte(const SV_Matte& m);

	virtual Material*
		clone(void) const;

	SV_Matte&
		operator= (const SV_Matte& rhs);

	~SV_Matte(void);

	void
		set_ka(const float k);

	void
		set_kd(const float k);

	void
		set_cd(const Texture* t_ptr);

	virtual RGBColor
		shade(ShadeRec& s);

	virtual RGBColor shade_caustics(ShadeRec& sr, Vector3D& lightDir);	//should return black

private:

	SV_Lambertian* ambient_brdf;
	SV_Lambertian* diffuse_brdf;
};

inline void
SV_Matte::set_cd(const Texture* t_ptr) {
	ambient_brdf->set_cd(t_ptr);
	diffuse_brdf->set_cd(t_ptr);
}

// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void
SV_Matte::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void
SV_Matte::set_kd(const float kd) {
	diffuse_brdf->set_kd(kd);
}

inline
RGBColor
SV_Matte::shade(ShadeRec& sr) {
	Vector3D 	wo = -sr.ray.d;
	RGBColor 	L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights = sr.w.lights.size();

	for (int j = 0; j < num_lights; j++) {
		Light* light_ptr = sr.w.lights[j];
		Vector3D wi = light_ptr->get_direction(sr);	//textbook says compute_direction, but couldn't find anything else
		wi.normalize();
		float ndotwi = sr.normal * wi;
		float ndotwo = sr.normal * wo;

		if (ndotwi > 0.0 && ndotwo > 0.0) {
			bool in_shadow = false;

	//		if (sr.w.lights[j]->casts_shadows()) {
	//			Ray shadow_ray(sr.hitPoint, wi);
	//			in_shadow = light_ptr->in_shadow(shadow_ray, sr.w.objects);
	//		}

			if (!in_shadow) {
				//G is from the area light section which we don't have yet
				//L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi;
				L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * ndotwi;
			}
				
		}
	}

	return (L);
}

inline RGBColor SV_Matte::shade_caustics(ShadeRec& sr, Vector3D& lightDir) {
	return RGBColor(black);
}
