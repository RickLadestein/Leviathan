#include "Mesh.h"
#include "Leviathan/Util/FileManager.h"
#include "Leviathan/Data/Dictionary.h"
#include <unordered_map>

namespace Leviathan::Graphics {
	unsigned int Mesh::GetPrimitiveCount()
	{
		int primitive_vertex_count;
		switch (this->primitive_type) {
		case PrimitiveType::POINT:
			primitive_vertex_count = 1;
			break;
		case PrimitiveType::LINE:
			primitive_vertex_count = 2;
			break;
		case PrimitiveType::TRIANGLES:
			primitive_vertex_count = 3;
			break;
		}
		return this->meshdata.verts.size() / primitive_vertex_count;
	}

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
		this->meshdata.verts.reserve(expectedsize);
		this->meshdata.norms.reserve(expectedsize);
		this->meshdata.texts.reserve(expectedsize);
	}

	void CustomMesh::AddMeshData(glm::vec3& vertex_pos, glm::vec3& normal, glm::vec3& texture_coord)
	{
		this->meshdata.verts.push_back(vertex_pos);
		this->meshdata.norms.push_back(normal);
		this->meshdata.texts.push_back(texture_coord);
	}

	void CustomMesh::AddMeshData(VertexData& vdata)
	{
		this->meshdata.verts.push_back(vdata.vertex);
		this->meshdata.norms.push_back(vdata.normal);
		this->meshdata.texts.push_back(vdata.texture);
	}

	void CustomMesh::ClearMeshData()
	{
		this->meshdata.verts.clear();
		this->meshdata.norms.clear();
		this->meshdata.texts.clear();
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
