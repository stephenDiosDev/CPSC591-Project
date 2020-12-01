// This builds a scene that consists of 35 shaded spheres and a plane.
// The objects are illuminated by a directional light and rendered with
// ambient and diffuse shading.
// Perspective viewing is used with a pinhole camera.
// Jittered sampling for antialiasing is hardwired into the PinHole::render_scene function.
// There are no sampler classes in this project.
// These are in the Chapter 5 download file.
// The spheres are the same as those in the Chapter 14 page one image. 
#include "Image.h"
#include "ImageTexture.h"
#include "SV_Matte.h"
#include "SphericalMap.h"
#include "ConstantColor.h"
#include "Instance.h"
void World::build(void) {
	int num_samples = 1;

	// colors

	RGBColor yellow(1, 1, 0);										// yellow
	RGBColor brown(0.71, 0.40, 0.16);								// brown
	RGBColor darkGreen(0.0, 0.41, 0.41);							// darkGreen
	RGBColor orange(1, 0.75, 0);									// orange
	RGBColor green(0, 0.6, 0.3);									// green
	RGBColor lightGreen(0.65, 1, 0.30);								// light green
	RGBColor darkYellow(0.61, 0.61, 0);								// dark yellow
	RGBColor lightPurple(0.65, 0.3, 1);								// light purple
	RGBColor darkPurple(0.5, 0, 1);									// dark purple
	RGBColor grey(0.65);
	RGBColor red(1, 0, 0);
	RGBColor sand(249,227,190);
	RGBColor water(0, 1, 2);


	// view plane  

	vp.set_hres(650);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples);

	// the ambient light here is the same as the default set in the World
	// constructor, and can therefore be left out

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);

	background_color = water;			// default color - this can be left out

	tracer_ptr = new RayCast(this);


	// camera

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(50, 15, 120);
	//pinhole_ptr->set_lookat(0, 0, -0.3);
	pinhole_ptr->set_lookat(0, 0, 0);
	pinhole_ptr->set_view_distance(1000);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);


	// light

	Directional* directional_ptr = new Directional;
	directional_ptr->set_direction(10, 10.30, -0.15);
	directional_ptr->scale_radiance(4.5);
	//directional_ptr->set_shadows(true);
	add_light(directional_ptr);

	// Matte material reflection coefficients - common to all materials

	float ka = 0.25;
	float kd = 0.75;


	//shark=================================================================================================================
	ConstantColor* constantColor = new ConstantColor;
	constantColor->set_color(grey);

	SV_Matte* svMattePtr = new SV_Matte;
	svMattePtr->set_ka(0.45);
	svMattePtr->set_kd(0.65);
	svMattePtr->set_cd(constantColor);


	
	char* file_name = "..\\wxRaytracer\\raytracer\\Models\\sharkTest.ply";
	Grid* grid_ptr = new Grid(new Mesh);
	grid_ptr->read_smooth_triangles(file_name);		// for Figure 23.7(b)
	grid_ptr->set_material(svMattePtr);
	grid_ptr->setup_cells();
	Instance* gridInstance = new Instance(grid_ptr);
	add_object(gridInstance);


	//chest=================================================================================================================
	ConstantColor* chestColour = new ConstantColor;
	chestColour->set_color(brown);

	SV_Matte* chestMatte = new SV_Matte;
	chestMatte->set_ka(0.45);
	chestMatte->set_kd(0.65);
	chestMatte->set_cd(chestColour);


	char* chestFileName = "..\\wxRaytracer\\raytracer\\Models\\testChest.ply";
	Grid* chestGrid = new Grid(new Mesh);
	chestGrid->read_smooth_triangles(chestFileName);		// for Figure 23.7(b)
	chestGrid->set_material(chestMatte);
	chestGrid->setup_cells();
	Instance* chestGridInstance = new Instance(chestGrid);
	add_object(chestGridInstance);


	//sand floor=================================================================================================================
	ConstantColor* sandColour = new ConstantColor;
	sandColour->set_color(sand);

	SV_Matte* sandMatte = new SV_Matte;
	sandMatte->set_ka(0.45);
	sandMatte->set_kd(0.65);
	sandMatte->set_cd(sandColour);


	char* sandFileName = "..\\wxRaytracer\\raytracer\\Models\\ocean\\sand.ply";
	Grid* sandGrid = new Grid(new Mesh);
	sandGrid->read_smooth_triangles(sandFileName);		// for Figure 23.7(b)
	sandGrid->set_material(sandMatte);
	sandGrid->setup_cells();
	Instance* sandGridInstance = new Instance(sandGrid);
	add_object(sandGridInstance);


	// vertical plane

	Matte* matte_ptr36 = new Matte;
	matte_ptr36->set_ka(ka);
	matte_ptr36->set_kd(kd);
	matte_ptr36->set_cd(water);
	Plane* plane_ptr = new Plane(Point3D(0, 0, -150), Normal(0, 0, 1));
	plane_ptr->set_material(matte_ptr36);
	add_object(plane_ptr);
}

