#ifndef __GRID__
#define __GRID__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This contains the declaration of the class Grid.
// The copy constructor, assignment operator, and destructor, are dummy functions.
// The reason is that a grid can contain an arbitrary number of objects, can therefore be of arbitrary size.


// There is no set_bounding_box function because the bounding box is constructed in the setup_cells
// function.

// This Grid class is also way too large. All the triangle and PLY file code should be placed in
// a separate class called TriangleMesh that inherits from Grid.


#include "Compound.h"
#include "ShadeRec.h"
#include "Mesh.h"
#include "BBox.h"
#include "Maths.h"
#include "AssimpLoader.h"


//---------------------------------------------------------------------- class Grid

class Grid: public Compound {										  	
	public:

		Grid(void); 

		Grid(Mesh* _mesh_ptr);    										

		virtual Grid* 										
		clone(void) const;

		Grid(const Grid& rg); 		

		Grid& 								
		operator= (const Grid& rhs);	

		virtual 										
		~Grid(void);   			

		virtual BBox 
		get_bounding_box(void);

		void												
		read_flat_triangles(char* file_name);

		void												
		read_smooth_triangles(char* file_name);

		void
		read_flat_uv_triangles(char* file_name);

		void
		read_smooth_uv_triangles(char* file_name);

		void												
		tessellate_flat_sphere(const int horizontal_steps, const int vertical_steps);

		void												
		tessellate_smooth_sphere(const int horizontal_steps, const int vertical_steps);

		virtual bool 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;		 					 

		void
		setup_cells(void);

		void
		reverse_mesh_normals(void);

		void
		store_material(Material* material, const int index); 		

		bool readObjWithAssimp(std::string filePath);

	private: 

		std::vector<GeometricObject*>	cells;			// grid of cells
		int							nx, ny, nz;    	// number of cells in the x, y, and z directions
		BBox						bbox;			// bounding box
		Mesh*						mesh_ptr;		// holds triangle data
		bool						reverse_normal;	// some PLY files have normals that point inwards

		Point3D
		find_min_bounds(void);

		Point3D
		find_max_bounds(void);

		void
		read_ply_file(char* file_name, const int triangle_type);

		void read_uv_ply_file(char* file_name, const int triangle_type);

		void
		compute_mesh_normals(void);	
};


// ------------------------------------------------------------------------------ store_material

inline void
Grid::reverse_mesh_normals(void) {   
	reverse_normal = true;
}


// ------------------------------------------------------------------------------ store_material
// stores the material in the specified object
// this is called from the Rosette and Archway classes, which inherit from Grid

inline void
Grid::store_material(Material* material_ptr, const int index) {
	objects[index]->set_material(material_ptr); 
}

//calls the AssimpTools methods
inline bool Grid::readObjWithAssimp(std::string filePath)
{
	std::vector<AssimpStructs::Vertex> verts;
	std::vector<int> indices;

	AssimpLoader* load = new AssimpLoader;
	load->loadModel(filePath);

	//copy all vertices and indices from the assimp data to our own
	for (int i = 0; i < load->meshes.size(); i++) {
		for (int j = 0; j < load->meshes[i].vertices.size(); j++) {
			verts.push_back(load->meshes[i].vertices[j]);
		}

		for (int k = 0; k < load->meshes[i].indices.size(); k++) {
			indices.push_back(load->meshes[i].indices[k]);
		}
	}

	//data needed to fill up mesh_ptr
	std::vector<Point3D> allVertices;
	std::vector<Normal> allNormals;
	std::vector<float> allU;
	std::vector<float> allV;
	std::vector<std::vector<int>> allFaces;
	int numVertices;
	int numTriangles;
	
	//fill up temp vars with data, then place them into above data
	for (int i = 0; i < verts.size(); i++) {
		Point3D point;
		Normal norm;
		float u, v;
		std::vector<int> face;

		point = verts[i].position;
		norm = verts[i].normal;
		u = verts[i].u;
		v = verts[i].v;
		face = verts[i].vertexFace;

		allVertices.push_back(point);
		allNormals.push_back(norm);
		allU.push_back(u);
		allV.push_back(v);
		allFaces.push_back(face);
	}

	numVertices = allVertices.size();
	numTriangles = allFaces.size();

	mesh_ptr->vertices = allVertices;
	mesh_ptr->normals = allNormals;
	mesh_ptr->u = allU;
	mesh_ptr->v = allV;
	mesh_ptr->vertex_faces = allFaces;
	mesh_ptr->num_triangles = numTriangles;
	mesh_ptr->num_vertices = numVertices;

	if (mesh_ptr->vertices.size() == numVertices)
		return true;
	else
		return false;
}

#endif









