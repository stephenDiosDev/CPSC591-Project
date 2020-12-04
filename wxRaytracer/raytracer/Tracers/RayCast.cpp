#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

// -------------------------------------------------------------------- default constructor

RayCast::RayCast(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor
		
RayCast::RayCast(World* _worldPtr)
	: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

RayCast::~RayCast(void) {}


// -------------------------------------------------------------------- trace_ray

RGBColor	
RayCast::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray));
		
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (sr.material_ptr->shade(sr));
	}   
	else
		return (world_ptr->background_color);
}


// -------------------------------------------------------------------- trace_ray
// this ignores the depth argument

RGBColor	
RayCast::trace_ray(const Ray ray, const int depth) const {
	ShadeRec sr(world_ptr->hit_objects(ray));		//where the objetc is hit plus normal at hit point is stored here
		
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading

		if (sr.material_ptr != nullptr)
			return (sr.material_ptr->shade(sr));		//returns rgbcolour
		else
			return(world_ptr->background_color);
	}   
	else
		return (world_ptr->background_color);
}


RGBColor
RayCast::trace_ray_caustics(const Ray ray, const int depth) const {
	ShadeRec sr(world_ptr->hit_objects(ray));		//where the objetc is hit plus normal at hit point is stored here

	//this ray goes from pixel to scene
	//from here at the point of impact stored in sr, we want to fire another ray straight upwards
	if (sr.hit_an_object) {
		Point3D causticSurface = sr.hit_point;
		Ray yRay(causticSurface, Vector3D(0, 1, 0));

		//return RGBColor(sr.normal.x, sr.normal.y, sr.normal.z);

		ShadeRec causticSr(world_ptr->hit_objects(yRay));	//where this new yRay hits
		if (causticSr.hit_an_object) {
			sr.ray = yRay;

			if (sr.material_ptr != nullptr) {
				//colour calculation for caustic white
				RGBColor causticsColour = causticSr.material_ptr->shade_caustics(causticSr, world_ptr->lights[0]->get_direction(causticSr));
				return causticsColour;
			}
			else {
				return RGBColor(black);
			}
		}
		else {
			return RGBColor(black);
		}
		
	}
	else
		return (world_ptr->background_color);	//hits background
	
}

