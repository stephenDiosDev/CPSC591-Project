# CPSC 591 Project
## Stephen Dios 30027675

### Google Drive Link
The below link goes to a google drive which contains all the rendered images, as well as the demo video and a link to the demo video on youtube:
https://drive.google.com/drive/folders/1G8-jkwJH25xM44345Qm4vxuislGWZdTA?usp=sharing


### How to Run
Ensure you have Visual Studio 2019 installed and open the file: wxRaytracerVCPP2005EE.sln
Then build the project and run it in Debug Mode.
Once the window has opened, click the menu bar button "Render" and wait for the render to complete.

Currently I only have one scene but you can carefully adjust code to get different options:

#### To adjust the number of ray samples per pixel
wxRaytracer/raytracer/build/BuildShadedObjects.cpp at Line 17.

#### To enable/disable the caustics function
wxRaytracer/raytracer/Cameras/Pinhole.cpp at Line 98
- Lines 98 and 99 correspond to the Nvidia caustics method
- Lines 101 and 102 correspond to the "forward" approximation

You can leave them both commented out for no caustics, or uncomment one to enable a particular caustics settings.


Additionally, you can comment out Line 92 of wxRaytracer/raytracer/Cameras/Pinhole.cpp and uncomment one of the caustics 
to get a grayscale image that just shows caustics in the scene.

#### To adjust parameters of the caustics function
wxRaytracer/raytracer/Tracers/RayCast.cpp at Line 96
- Here you can adjust details about the "Forward" caustics function. Particularly, Line 138 adjusts the tolerance value (larger = more caustics).

wxRaytracer/raytracer/Materials/MatteWave.cpp at Line 102
- Here you can adjust details about the Nvidia caustics function. Particularly, Line 145 adjusts the angle cut off (larger = more caustics).
