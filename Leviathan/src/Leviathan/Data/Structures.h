#pragma once
#include "glm/glm.hpp"
#include <inttypes.h>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <memory>
#include "Dictionary.h"
#include <list>

typedef std::uint8_t byte;
typedef unsigned int Handle;

enum class PrimitiveType : GLenum {
    TRIANGLES = GL_TRIANGLES,
    LINE = GL_LINES,
    POINT = GL_POINTS
};

enum class AttributeType : GLenum {
    UINTEGER = GL_UNSIGNED_INT,
    INTEGER = GL_INT,
    FLOAT = GL_FLOAT,
    BOOLEAN = GL_BOOL
};

struct PlayerCoords {
    float x;
    float y;
};

struct MeshData {
    /// <summary>
    /// Vertex data container
    /// </summary>
    std::vector<glm::vec3> verts;

    /// <summary>
    /// Normal data container
    /// </summary>
    std::vector<glm::vec3> norms;

    /// <summary>
    /// Texture data container
    /// </summary>
    std::vector<glm::vec3> texts;

    //The amount of primitives stored inside this data
    int primitive_count;

    //The type of primitive
    PrimitiveType primitive_type;
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

union TrianglePrimitive {
    struct
    {
        VertexData v1;
        VertexData v2;
        VertexData v3;
    };
    float data[(sizeof(VertexData) / sizeof(float)) * 3];
};

union LinePrimitive {
    struct
    {
        VertexData v1;
        VertexData v2;
    };
    float data[(sizeof(VertexData) / sizeof(float)) * 2];
};

struct Attribute {
protected:
    std::string name;
    AttributeType base_type;
    size_t components = 0;
    size_t base_type_size = 0;
    size_t datapoints = 0;

    
private:
    void AddData(void* valueptr, size_t bytesize) {
        byte* bdata = new byte[bytesize];
        memcpy(bdata, valueptr, bytesize);
        for (int i = 0; i < bytesize; i++) {
            data.push_back(bdata[i]);
        }
    }

public:
    std::vector<byte> data;

    inline AttributeType GetBaseType() { return this->base_type; }
    inline size_t GetComponents() { return this->components; }
    inline size_t GetBaseTypeSize() { return this->base_type_size; }
    inline std::string GetName() { return this->name; }
    inline size_t GetDataPointCount() { return this->datapoints; }
    inline void ClearData() { this->data.clear(); }

#pragma region Bool_AddData
    void AddData(bool value) {
        if (base_type == AttributeType::BOOLEAN && components == 1) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::bvec2 value) {
        if (base_type == AttributeType::BOOLEAN && components == 2) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::bvec3 value) {
        if (base_type == AttributeType::BOOLEAN && components == 3) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::bvec4 value) {
        if (base_type == AttributeType::BOOLEAN && components == 4) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }
#pragma endregion
#pragma region Bool_List_AddData
    void AddData(std::vector<glm::bvec1>& values) {
        if (base_type == AttributeType::BOOLEAN && components == 1) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::bvec2>& values) {
        if (base_type == AttributeType::BOOLEAN && components == 2) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::bvec3>& values) {
        if (base_type == AttributeType::BOOLEAN && components == 3) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::bvec4>& values) {
        if (base_type == AttributeType::BOOLEAN && components == 4) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }
#pragma endregion

#pragma region Unsigned_Int_AddData
    void AddData(unsigned int value) {
        if (base_type == AttributeType::UINTEGER && components == 1) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::uvec2 value) {
        if (base_type == AttributeType::UINTEGER && components == 2) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::uvec3 value) {
        if (base_type == AttributeType::UINTEGER && components == 3) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::uvec4 value) {
        if (base_type == AttributeType::UINTEGER && components == 4) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }
#pragma endregion
#pragma region Unsigned_Int_List_AddData
    void AddData(std::vector<unsigned int>& values) {
        if (base_type == AttributeType::UINTEGER && components == 1) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::uvec2>& values) {
        if (base_type == AttributeType::UINTEGER && components == 2) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::uvec3>& values) {
        if (base_type == AttributeType::UINTEGER && components == 3) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::uvec4>& values) {
        if (base_type == AttributeType::UINTEGER && components == 4) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }
#pragma endregion

#pragma region Int_AddData
    void AddData(int value) {
        if (base_type == AttributeType::INTEGER && components == 1) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::ivec2 value) {
        if (base_type == AttributeType::INTEGER && components == 2) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::ivec3 value) {
        if (base_type == AttributeType::INTEGER && components == 3) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::ivec4 value) {
        if (base_type == AttributeType::INTEGER && components == 4) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }
#pragma endregion
#pragma region Int_List_AddData
    void AddData(std::vector<int>& values) {
        if (base_type == AttributeType::INTEGER && components == 1) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::ivec2>& values) {
        if (base_type == AttributeType::INTEGER && components == 2) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::ivec3>& values) {
        if (base_type == AttributeType::INTEGER && components == 3) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::ivec4>& values) {
        if (base_type == AttributeType::INTEGER && components == 4) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }
#pragma endregion

#pragma region Float_AddData
    void AddData(float value) {
        if (base_type == AttributeType::FLOAT && components == 1) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::vec2 value) {
        if (base_type == AttributeType::FLOAT && components == 2) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::vec3 value) {
        if (base_type == AttributeType::FLOAT && components == 3) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(glm::vec4 value) {
        if (base_type == AttributeType::FLOAT && components == 4) {
            size_t bytesize = components * base_type_size;
            this->AddData(&value, bytesize);
            this->datapoints += 1;
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }
#pragma endregion
#pragma region Float_List_AddData
    void AddData(std::vector<float>& values) {
        if (base_type == AttributeType::FLOAT && components == 1) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::vec2>& values) {
        if (base_type == AttributeType::FLOAT && components == 2) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::vec3>& values) {
        if (base_type == AttributeType::FLOAT && components == 3) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }

    void AddData(std::vector<glm::vec4>& values) {
        if (base_type == AttributeType::FLOAT && components == 4) {
            size_t bytesize = components * base_type_size * values.size();
            this->AddData(values.data(), bytesize);
            this->datapoints += values.size();
        }
        else {
            throw std::exception("value type and components do not match with Attribute");
        }
    }
#pragma endregion
};

template<typename T>
struct AttributeData;



#pragma region Integer_Attribute_Data
template<> struct AttributeData<int>: public Attribute {
    AttributeData() {
        base_type = AttributeType::INTEGER;
        components = 1;
        base_type_size = sizeof(int);
    }
};

template<> struct AttributeData<glm::ivec2> : public Attribute {
    AttributeData() {
        base_type = AttributeType::INTEGER;
        components = 2;
        base_type_size = sizeof(int);
    }
};

template<> struct AttributeData<glm::ivec3> : public Attribute {
    AttributeData() {
        base_type = AttributeType::INTEGER;
        components = 3;
        base_type_size = sizeof(int);
    }
};

template<> struct AttributeData<glm::ivec4> : public Attribute {
    AttributeData() {
        base_type = AttributeType::INTEGER;
        components = 4;
        base_type_size = sizeof(int);
    }
};
#pragma endregion

#pragma region Unsigned_Integer_Attribute_Data
template<> struct AttributeData<unsigned int> : public Attribute {
    AttributeData() {
        base_type = AttributeType::UINTEGER;
        components = 1;
        base_type_size = sizeof(int);
    }
};

template<> struct AttributeData<glm::uvec2> : public Attribute {
    AttributeData() {
        base_type = AttributeType::UINTEGER;
        components = 2;
        base_type_size = sizeof(int);
    }
};

template<> struct AttributeData<glm::uvec3> : public Attribute {
    AttributeData() {
        base_type = AttributeType::UINTEGER;
        components = 3;
        base_type_size = sizeof(int);
    }
};

template<> struct AttributeData<glm::uvec4> : public Attribute {
    AttributeData() {
        base_type = AttributeType::UINTEGER;
        components = 4;
        base_type_size = sizeof(int);
    }
};
#pragma endregion

#pragma region Bool_Attribute_Data
template<> struct AttributeData<bool> : public Attribute {
    AttributeData() {
        base_type = AttributeType::BOOLEAN;
        components = 1;
        base_type_size = sizeof(bool);
    }
};

template<> struct AttributeData<glm::bvec2> : public Attribute {
    AttributeData() {
        base_type = AttributeType::BOOLEAN;
        components = 2;
        base_type_size = sizeof(bool);
    }
};

template<> struct AttributeData<glm::bvec3> : public Attribute {
    AttributeData() {
        base_type = AttributeType::BOOLEAN;
        components = 3;
        base_type_size = sizeof(bool);
    }
};

template<> struct AttributeData<glm::bvec4> : public Attribute {
    AttributeData() {
        base_type = AttributeType::BOOLEAN;
        components = 4;
        base_type_size = sizeof(bool);
    }
};
#pragma endregion

#pragma region Float_Attribute_Data
template<> struct AttributeData<float> : public Attribute {
    AttributeData() {
        base_type = AttributeType::FLOAT;
        components = 1;
        base_type_size = sizeof(float);
    }
};

template<> struct AttributeData<glm::vec2> : public Attribute {
    AttributeData() {
        base_type = AttributeType::FLOAT;
        components = 2;
        base_type_size = sizeof(float);
    }
};

template<> struct AttributeData<glm::vec3> : public Attribute {
    AttributeData() {
        base_type = AttributeType::FLOAT;
        components = 3;
        base_type_size = sizeof(float);
    }
};

template<> struct AttributeData<glm::vec4> : public Attribute {
    AttributeData() {
        base_type = AttributeType::FLOAT;
        components = 4;
        base_type_size = sizeof(float);
    }
};
#pragma endregion

struct AttributeStorage {
private:
    Leviathan::Dictionary<std::string, std::shared_ptr<Attribute>> attribs;
    std::list<std::string> order;
public:
    std::list<std::string> GetOrder() {
        return this->order;
    }

    template<typename valuetype>
    void AddAttribute(std::string name) {
        std::shared_ptr<Attribute> ptr;
        bool succes = attribs.try_get_value(name, ptr);
        if (succes) {
            throw std::exception("A attribute with that name already exists");
        }
        else {
            ptr = std::make_shared<AttributeData<valuetype>>();
            attribs[name] = ptr;
            this->order.push_back(name);
        }
    }

    std::shared_ptr<Attribute> GetAttribute(std::string name) {
        std::shared_ptr<Attribute> ptr;
        bool succes = attribs.try_get_value(name, ptr);
        if (succes) {
            return ptr;
        }
        else {
            throw std::exception("A attribute with that name already exists");
            return nullptr;
        }
    }

    bool RemoveAttribute(std::string name) {
        bool succes = attribs.try_erase(name);
        if (succes) {
            order.remove(name);
        }
    }
};