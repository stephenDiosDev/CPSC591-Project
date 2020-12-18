#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <iostream>
#include <vector>
#include "AssimpStructs.h"
#include "Point3D.h"
#include "Normal.h"


//the following code was taken and adapted from here:
//https://learnopengl.com/Model-Loading/Model
//https://learnopengl.com/Model-Loading/Mesh
//https://learnopengl.com/Model-Loading/Assimp
class AssimpLoader
{
public:
    //holds the finish mesh list
    std::vector<AssimpStructs::AssimpMesh> meshes;
    //std::vector<AssimpStructs::Triangle> triangles;

	void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    AssimpStructs::AssimpMesh processMesh(aiMesh* mesh, const aiScene* scene);

private:

};

inline void AssimpLoader::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    std::string directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

inline void AssimpLoader::processNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

inline AssimpStructs::AssimpMesh AssimpLoader::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<AssimpStructs::Vertex> verts;
    std::vector<int> indices;
    bool hasZero = false;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        AssimpStructs::Vertex vertex;
        //process vertex

        //position
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        //normal
        if (mesh->HasNormals()) {
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
        }

        

        //texture coords
        if (mesh->mTextureCoords[0]) {  //if they exist
            vertex.u = mesh->mTextureCoords[0][i].x;
            vertex.v = mesh->mTextureCoords[0][i].y;
        }
        else {
            vertex.u = 0.0;
            vertex.v = 0.0;
        }

        verts.push_back(vertex);
    }

    //process indices
    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        if (face.mNumIndices == 3) {    //triangle
            float ind0 = face.mIndices[0];      //makes up one face
            float ind1 = face.mIndices[1];
            float ind2 = face.mIndices[2];

            if (ind0 == 0 || ind1 == 0 || ind2 == 0)
                hasZero = true;

            std::vector<int> faces;
            faces.push_back(ind0);
            faces.push_back(ind1);
            faces.push_back(ind2);
/*
            AssimpStructs::Triangle triangle;
            triangle.triFace = faces;
            triangle.a = verts[ind0];
            triangle.b = verts[ind1];
            triangle.c = verts[ind2];
            triangles.push_back(triangle);
  */    
            verts[ind0].vertexFace = faces;
            verts[ind1].vertexFace = faces;
            verts[ind2].vertexFace = faces;

            indices.push_back(ind0);
            indices.push_back(ind1);
            indices.push_back(ind2);
        }
    }
    AssimpStructs::AssimpMesh myMesh(verts, indices);
    return myMesh;
}