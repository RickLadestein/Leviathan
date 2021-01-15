#pragma once
#include "glm/glm.hpp"
#include <inttypes.h>
#include <string>
#include <vector>
#include <glad/glad.h>

typedef std::uint8_t byte;
typedef unsigned int Handle;

struct PlayerCoords {
    float x;
    float y;
};

union VertexData {
    struct
    {
        glm::vec3 vertex;
        glm::vec3 normal;
        glm::vec3 texture;
    };
    float data[(sizeof(glm::vec3) / sizeof(float)) * 3];
};

union Primitive {
    struct
    {
        VertexData v1;
        VertexData v2;
        VertexData v3;
    };
    float data[(sizeof(VertexData) / sizeof(float)) * 3];
};

struct Attribute {
    std::string name;
    size_t size;
    size_t offset;
    size_t stride;
};

template<typename V, typename N, typename T>
union TripleVertexData {
    struct
    {
        V vertex;
        N normal;
        T texture;
    };
    byte data[sizeof(V) + sizeof(N) + sizeof(T)];
};

template<typename V, typename N>
union DoubleVertexData {
    struct
    {
        V vertex;
        N normal;
    };
    byte data[sizeof(V) + sizeof(N)];
};

template<typename V>
union SingleVertexData {
    struct
    {
        V vertex;
    };
    byte data[sizeof(V)];
};

struct _Primitive {
    std::vector<byte> vertex_data;

    void copyDataFromSource(const void* src, size_t size) {
        vertex_data.clear();
        vertex_data.resize(size);
        byte* vdata_ptr = vertex_data.data();
        memmove(vdata_ptr, src, size);
    }
};

enum class PrimitiveType : GLenum {
    TRIANGLES = GL_TRIANGLES,
    LINE = GL_LINES,
    POINT = GL_POINTS
};
