#ifndef __RAY_CAST__
#define __RAY_CAST__

#include "Tracer.h"

class RayCast: public Tracer {
	public:
		
		RayCast(void);
		
		RayCast(World* _worldPtr);
				
		virtual											
		~RayCast(void);		

		virtual RGBColor	
		trace_ray(const Ray& ray) const;

		virtual RGBColor	
		trace_ray(const Ray ray, const int depth) const;

		virtual RGBColor trace_ray_caustics(const Ray ray, const int depth) const;

		virtual RGBColor trace_ray_forward_caustics(const Ray ray, const int depth) const;
};

#endif