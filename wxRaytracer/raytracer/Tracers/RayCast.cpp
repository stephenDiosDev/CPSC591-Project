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

RGBColor
RayCast::trace_ray_forward_caustics(const Ray ray, const int depth) const {
	ShadeRec sr(world_ptr->hit_objects(ray));	//we hit somewhere in the scene

	if (sr.hit_an_object) {	//will either hit scene or background
		Point3D sceneHitPoint = sr.hit_point;
		Point3D lightPos(0, 1000, 0);
		Vector3D lightDir = sceneHitPoint - lightPos;
		Ray lightRay(lightPos, lightDir);

		//return RGBColor(sr.normal.x, sr.normal.y, sr.normal.z);
		ShadeRec forwardCaustics(world_ptr->hit_objects(lightRay));
		if (forwardCaustics.hit_an_object) {						//can only hit a wave or background
			//transmission ray equation
			Vector3D N = forwardCaustics.normal;
			Vector3D E = lightRay.d;
			float ior = 1.33;

			float squareRoot = 1 + (pow(ior, 2)) * (pow((E * N), 2) - 1);
			bool positive = true;
			if (squareRoot < 0)
				positive = false;

			squareRoot = sqrt(abs(squareRoot));

			float brackets = ior * (E * N);
			if (positive)
				brackets += squareRoot;
			else
				brackets -= squareRoot;

			Vector3D Tdir = (N * brackets) + (ior * E);
			Ray T(forwardCaustics.hit_point, Tdir);

			ShadeRec finalCaustics(world_ptr->hit_objects(T));
			if (finalCaustics.hit_an_object) {
				float strength = 0;

				Point3D causticHitPoint(finalCaustics.hit_point);
				Point3D actualPoint(sr.hit_point);

				
				//float tolerance = 0.0000008;
				float tolerance = 0.0000007;
				//float tolerance = 0.000002;
				float distance = sqrt((pow((actualPoint.x - causticHitPoint.x), 2)) + (pow((actualPoint.y - causticHitPoint.y), 2)) + (pow((actualPoint.z - causticHitPoint.z), 2)));
				strength = (tolerance - distance) / tolerance;
				
				if (strength < 0)
					strength = 0;
				else if (strength > 1)
					strength = 1;
					
				return RGBColor(white) * strength;

			}
			else
				return RGBColor(0, 0, 0);

		}
		else
			return (world_ptr->background_color);
	}
	else
		return (world_ptr->background_color);	//hits background

}

