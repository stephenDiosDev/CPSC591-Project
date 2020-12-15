#pragma once
class AssimpStructs
{
public:
    //a middle man struct to hold info
    struct Vertex {
        Point3D position;
        Normal normal;
        float u;
        float v;
        std::vector<int> vertexFace;
    };

    struct AssimpMesh {
        std::vector<Vertex> vertices;
        std::vector<int> indices;

        AssimpMesh(std::vector<Vertex> verts, std::vector<int> indix) {
            this->vertices = verts;
            this->indices = indix;
        }
    };
};

