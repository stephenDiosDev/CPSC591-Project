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
        int index;

        Vertex& operator= (const Vertex& rhs);
    };

    struct Triangle {
        Vertex a;
        Vertex b;
        Vertex c;
        std::vector<int> triFace;

        Triangle& operator= (const Triangle& rhs);
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

inline AssimpStructs::Vertex& AssimpStructs::Vertex::operator=(const Vertex& rhs)
{
    if (this == &rhs)
        return (*this);

    position = rhs.position;
    normal = rhs.normal;
    u = rhs.u;
    v = rhs.v;
    index = rhs.index;

    return (*this);
}

inline AssimpStructs::Triangle& AssimpStructs::Triangle::operator=(const Triangle& rhs) {
    if (this == &rhs)
        return (*this);
    a = rhs.a;
    b = rhs.b;
    c = rhs.c;

    triFace = rhs.triFace;

    return (*this);
}


