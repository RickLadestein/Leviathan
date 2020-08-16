#pragma once
#include "glm/glm.hpp"
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