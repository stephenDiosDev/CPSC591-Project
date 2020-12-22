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
#include "MatteWave.h"
#include "SphericalMap.h"
#include "ConstantColor.h"
#include "Instance.h"
void World::build(void) {
	int num_samples = 16;

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
	RGBColor sand(0.24,0.22,0.19);
	RGBColor water(0, 0.07, 0.2);
	RGBColor wave(0, 0.250, 0.241);


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

	pinhole_ptr->set_eye(50, 40, 100);
	//pinhole_ptr->set_lookat(0, 0, -0.3);
	pinhole_ptr->set_lookat(0, 4, 0);
	pinhole_ptr->set_view_distance(1000);

	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);


	// light

	Directional* directional_ptr = new Directional;
	directional_ptr->set_direction(0, 1000, 0);
	directional_ptr->scale_radiance(4.5);
	directional_ptr->set_shadows(true);
	add_light(directional_ptr);

	// Matte material reflection coefficients - common to all materials

	float ka = 0.25;
	float kd = 0.75;

	//shark=================================================================================================================

	ConstantColor* constantColor = new ConstantColor;
	constantColor->set_color(grey);

	//Image* sharkTexture = new Image(1024,512);
	Image* sharkTexture = new Image();
	//sharkTexture->read_ppm_file("..\\wxRaytracer\\raytracer\\Textures\\ppm\\shark.ppm");
	char* sharkPath = "..\\wxRaytracer\\raytracer\\Textures\\ppm\\shark.ppm";
	sharkTexture->readTexture(sharkPath);

	ImageTexture* sharkImgTexture = new ImageTexture;
	sharkImgTexture->set_image(sharkTexture);
	sharkImgTexture->set_mapping(NULL);

	SV_Matte* svMattePtr = new SV_Matte;
	svMattePtr->set_ka(0.45);
	svMattePtr->set_kd(0.65);
	svMattePtr->set_cd(constantColor);
	//svMattePtr->set_cd(sharkImgTexture);

	string file_name = "..\\wxRaytracer\\raytracer\\Models\\oceanFinal\\shark.obj";
	Grid* grid_ptr = new Grid(new Mesh);

	grid_ptr->readObjWithAssimp(file_name);
	grid_ptr->set_material(svMattePtr);
	grid_ptr->setup_cells();
	Instance* gridInstance = new Instance(grid_ptr);
	add_object(gridInstance);


	//chest=================================================================================================================
	ConstantColor* chestColour = new ConstantColor;
	chestColour->set_color(brown);
	Image* chestTexture = new Image();
	//Image* chestTexture = new Image(2560,1280);
	chestTexture->read_ppm_file("..\\wxRaytracer\\raytracer\\Textures\\ppm\\chest.ppm");
	//chestTexture->read_ppm_file("..\\wxRaytracer\\raytracer\\Models\\originals\\treasure_chest.jpg");

	ImageTexture* chestImgTexture = new ImageTexture;
	chestImgTexture->set_image(chestTexture);
	chestImgTexture->set_mapping(NULL);

	SV_Matte* chestMatte = new SV_Matte;
	chestMatte->set_ka(0.45);
	chestMatte->set_kd(0.65);
	chestMatte->set_cd(chestColour);
	//chestMatte->set_cd(chestImgTexture);


	string chestFileName = "..\\wxRaytracer\\raytracer\\Models\\oceanFinal\\chest.obj";
	//string chestFileName = "..\\wxRaytracer\\raytracer\\Models\\originals\\chest.obj";
	Grid* chestGrid = new Grid(new Mesh);
	chestGrid->readObjWithAssimp(chestFileName);

	chestGrid->set_material(chestMatte);
	chestGrid->setup_cells();
	Instance* chestGridInstance = new Instance(chestGrid);
	add_object(chestGridInstance);


	//sand floor=================================================================================================================
	ConstantColor* sandColour = new ConstantColor;
	sandColour->set_color(sand);

	Image* sandTexture = new Image(800,600);
	
	sandTexture->read_ppm_file("..\\wxRaytracer\\raytracer\\Textures\\ppm\\sand2.ppm");

	ImageTexture* sandImgTexture = new ImageTexture;
	sandImgTexture->set_image(sandTexture);
	sandImgTexture->set_mapping(NULL);

	SV_Matte* sandMatte = new SV_Matte;
	sandMatte->set_ka(0.45);
	sandMatte->set_kd(0.65);
	//sandMatte->set_cd(sandColour);
	sandMatte->set_cd(sandImgTexture);

	string sandFileName = "..\\wxRaytracer\\raytracer\\Models\\oceanFinal\\sand.obj";
	Grid* sandGrid = new Grid(new Mesh);
	sandGrid->readObjWithAssimp(sandFileName);
	sandGrid->set_material(sandMatte);
	sandGrid->setup_cells();
	Instance* sandGridInstance = new Instance(sandGrid);
	add_object(sandGridInstance);


	//waves=================================================================================================================
	ConstantColor* wavesColour = new ConstantColor;
	wavesColour->set_color(water);

	MatteWave* waveMatte = new MatteWave;
	waveMatte->set_ka(0.45);
	waveMatte->set_kd(0.65);


	string waveFileName = "..\\wxRaytracer\\raytracer\\Models\\oceanFinal\\wave.obj";
	Grid* waveGrid = new Grid(new Mesh);
	waveGrid->readObjWithAssimp(waveFileName);
	waveGrid->set_material(waveMatte);
	waveGrid->setup_cells();
	Instance* waveGridInstance = new Instance(waveGrid);
	add_object(waveGridInstance);

	//debug cube============================================================================================================
	Image* cubeTexture = new Image();

	char* cubeTexFile = "..\\wxRaytracer\\raytracer\\Models\\testFiles\\colourTest.jpg";
	bool testResult = cubeTexture->readTexture(cubeTexFile);
	if (!testResult)
		exit(EXIT_FAILURE);

	ImageTexture* cubeImgTexture = new ImageTexture;
	cubeImgTexture->set_image(cubeTexture);
	cubeImgTexture->set_mapping(NULL);

	SV_Matte* cubeMatte = new SV_Matte;
	cubeMatte->set_ka(0.45);
	cubeMatte->set_kd(0.65);
	cubeMatte->set_cd(cubeImgTexture);

	string cubeFileName = "..\\wxRaytracer\\raytracer\\Models\\testFiles\\cube.obj";
	Grid* cubeGrid = new Grid(new Mesh);
	cubeGrid->readObjWithAssimp(cubeFileName);
	cubeGrid->set_material(cubeMatte);
	cubeGrid->setup_cells();
	Instance* cubeGridInstance = new Instance(cubeGrid);
	//add_object(cubeGridInstance);

}

