#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <iostream>
#include <vector>
#include "Point3D.h"
#include "Normal.h"


//the following code was taken and adapted from here:
//https://learnopengl.com/Model-Loading/Model
//https://learnopengl.com/Model-Loading/Mesh
//https://learnopengl.com/Model-Loading/Assimp
class AssimpLoader
{
    //a middle man struct to hold info
    struct Vertex {
        Point3D position;
        Normal normal;
        float u;
        float v;
        std::vector<int> vertexFace;
    };

    struct AssimpMesh {
        AssimpMesh(std::vector<Vertex> verts, std::vector<int> indix) {
            this->vertices = verts;
            this->indices = indix;
        }

        std::vector<Vertex> vertices;
        std::vector<int> indices;
    };

    std::vector<AssimpMesh> meshes;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
    AssimpMesh processMesh(aiMesh* mesh, const aiScene* scene);

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

    inline AssimpMesh AssimpLoader::processMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> verts;
        std::vector<int> indices;

        for (int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            //process vertex

            //position
            vertex.position.x = mesh->mVertices[i].x;
            vertex.position.y = mesh->mVertices[i].y;
            vertex.position.z = mesh->mVertices[i].z;

            //normal
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;

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
                float ind0 = face.mIndices[0];
                float ind1 = face.mIndices[1];
                float ind2 = face.mIndices[2];
                std::vector<int> faces;
                faces.push_back(ind0);
                faces.push_back(ind1);
                faces.push_back(ind2);

                verts[(i * 3) + 0].vertexFace = faces;
                verts[(i * 3) + 1].vertexFace = faces;
                verts[(i * 3) + 2].vertexFace = faces;

                indices.push_back(ind0);
                indices.push_back(ind1);
                indices.push_back(ind2);
            }
        }

        return AssimpMesh(verts, indices);
    }
};

