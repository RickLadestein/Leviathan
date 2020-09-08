#pragma once
#include "Leviathan/Core.h"
#include <string>
#include <vector>
#include "Leviathan/Data/Structures.h"
#include <memory>
class Mesh {
public:
	std::string name;
	std::vector<Primitive> data;
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