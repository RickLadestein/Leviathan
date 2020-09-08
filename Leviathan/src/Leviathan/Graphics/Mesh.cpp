#include "Mesh.h"
#include <unordered_map>
#include "Leviathan/Util/FileManager.h"
Mesh::Mesh(std::string src)
{
	
}

Mesh::Mesh(std::string folder, std::string file)
{
	FileManager::ImportObjFile(folder, file, this->data);
	if (this->data.size() > 0) {
		this->ready = true;
	}
	else {
		this->ready = false;
	}
}


std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
bool Mesh::AddMesh(std::string mesh_id, std::string folder_id, std::string mesh_file)
{
	try {
		if (meshes.at(mesh_id)) {
			return false;
		}
	}
	catch (std::exception e) {
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(folder_id, mesh_file);
		if (mesh->ready) {
			meshes[mesh_id] = mesh;
			return true;
		}
	}
	return false;
}

std::weak_ptr<Mesh> Mesh::GetMesh(std::string id)
{
	try {
		return meshes.at(id);
	}
	catch (std::exception e) {
		return std::weak_ptr<Mesh>();
	}
}

bool Mesh::DeleteMesh(std::string id)
{
	try {
		std::weak_ptr<Mesh> prg = meshes.at(id);
		meshes.erase(id);
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}
