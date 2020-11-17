#ifndef MESHOBJ_H
#define MESHOBJ_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <../glm-0.9.8.2/glm/glm.hpp>
#include <../glm-0.9.8.2/glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
using namespace std;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class MeshOBJ {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;

    // constructor
    MeshOBJ(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
    }

 
};
#endif