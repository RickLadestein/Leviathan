#include "Mesh.h"
#include "Leviathan/Util/FileManager.h"
#include "Leviathan/Data/Dictionary.h"
#include <unordered_map>

namespace Leviathan::Graphics {
	ModelMesh::ModelMesh(std::string folder, std::string file)
	{
		//import the mesh data from file
		this->attribs.AddAttribute<glm::vec3>("vertices");
		this->attribs.AddAttribute<glm::vec3>("normals");
		this->attribs.AddAttribute<glm::vec3>("texcoords");

		this->primitive_type = PrimitiveType::TRIANGLES;
		std::shared_ptr<Attribute> vertex_attrib = this->attribs.GetAttribute("vertices");
		std::shared_ptr<Attribute> normal_attrib = this->attribs.GetAttribute("normals");
		std::shared_ptr<Attribute> texcoord_attrib = this->attribs.GetAttribute("texcoords");

		this->status = MeshStatus::IMPORTING_DATA;
		bool succes = FileManager::ImportObjFile(folder, file, vertex_attrib, normal_attrib, texcoord_attrib);
		if (!succes) {
			this->status = MeshStatus::FAILED_IMPORT;
			return;
		}
		this->status = MeshStatus::BUILDING_BUFFER;
		this->vertex_buffer.BufferData(this->attribs);
		this->primitive_count = vertex_attrib->data.size() / (3 * sizeof(glm::vec3));

		this->status = MeshStatus::READY;
	}

	CustomMesh::CustomMesh(PrimitiveType type,size_t expectedsize)
	{
		this->primitive_type = type;
	}
	void CustomMesh::Build()
	{
	}


	Leviathan::Dictionary<std::string, MeshReference> mesh_storage;
	bool MeshStorage::AddMesh(std::string mesh_id, MeshReference mesh)
	{
		MeshReference found;
		bool succes = mesh_storage.try_get_value(mesh_id, found);
		if (succes) {
			throw std::exception("Could not add mesh: mesh already exists");
			return false;
		}
		else {
			mesh_storage[mesh_id] = mesh;
			return true;
		}
	}
	bool MeshStorage::DeleteMesh(std::string mesh_id)
	{
		MeshReference found;
		bool succes = mesh_storage.try_erase(mesh_id);
		return succes;

	}
	WeakMeshReference MeshStorage::GetMesh(std::string mesh_id)
	{
		MeshReference found;
		mesh_storage.try_get_value(mesh_id, found);
		return found;
	}
}
