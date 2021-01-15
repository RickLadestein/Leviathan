#pragma once
#include "Leviathan/Data/Structures.h"

#include <string>
#include <vector>
#include <memory>

namespace Leviathan::Graphics {
	class Mesh {
	public:
		std::string name;
		std::vector<byte> primitive_data;
		int primitive_count;
		PrimitiveType primitive_type;
		bool ready;

		Mesh(const Mesh&) = default;
		Mesh& operator=(const Mesh&) = default;
		Mesh(std::string src);
		Mesh(std::string folder, std::string file);
		Mesh() = delete;
		~Mesh() = default;
	public:

		static bool AddMesh(std::string mesh_id, std::string folder_id, std::string mesh_file);
		static std::weak_ptr<Mesh> GetMesh(std::string id);
		static bool DeleteMesh(std::string id);
	};
}