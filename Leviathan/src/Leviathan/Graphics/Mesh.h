#pragma once
#include "Leviathan/Data/Structures.h"
#include <string>
#include <vector>
#include <memory>
#include "Leviathan/Graphics/Buffers/VertexBuffer.h"

namespace Leviathan::Graphics {
	enum class MeshStatus {
		NOT_READY = -1,			//Object is created but nothing was done/imported yet
		IMPORTING_DATA = 1,		//Importing obj data from file
		FAILED_IMPORT = -2,		//Failed obj data import
		PARSING_DATA = 2,		//Parsing the vertex/normal/texture data from loaded file
		FAILED_PARSE = -3,		//Failed parsing the vertex/normal/texture data from loaded file
		BUILDING_BUFFER = 3,    //Creating the vertex buffer in memory
		FAILED_BUILD = -4,		//Failed creating vertex buffer
		READY = 0				//All set to go
	};

	class Mesh {
	public:
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		~Mesh() = default;
		
		Leviathan::Graphics::Buffers::VertexBuffer vertex_buffer;
		inline MeshStatus GetStatus() { return this->status; }
		PrimitiveType GetPrimitiveType() { return this->primitive_type; }
		int primitive_count;
	protected:
		Mesh() = default;
		MeshStatus status;
		std::string name;
		PrimitiveType primitive_type;
	};

	typedef std::shared_ptr<Mesh> MeshReference;
	typedef std::weak_ptr<Mesh> WeakMeshReference;

	class ModelMesh : public Mesh {
	public:
		ModelMesh(std::string folder, std::string file);
		~ModelMesh() = default;
	private:
		AttributeStorage attribs;
	};

	class CustomMesh: public Mesh {
	public: 
		CustomMesh(PrimitiveType type, size_t expectedsize = 100);
		void Build();

		AttributeStorage attribs;
	};

	class MeshStorage {
	public:
		static bool AddMesh(std::string mesh_id, MeshReference mesh);
		static bool DeleteMesh(std::string mesh_id);
		static WeakMeshReference GetMesh(std::string mesh_id);
	};

	
	
}