#include "FileManager.h"
#include "tiny_obj_loader.h"

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstddef>
#include <filesystem>
#include "Leviathan/Data/Dictionary.h"


using Leviathan::Image;

Leviathan::Dictionary<std::string, std::string> dict;

bool FileManager::RegisterDirectory(std::string folder_id, std::string path, bool overwrite)
{
	try {
		std::string res;
		bool succes = dict.try_get_value(folder_id, res);
		if (succes && overwrite || !succes) {
			dict[folder_id] = path;
			return true;
		}
		return false;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

bool FileManager::UnregisterDirectory(std::string folder_id)
{
	return dict.try_erase(folder_id);
}

std::string FileManager::GetDirectory(std::string folder_id)
{
	std::string result = "";
	try {
		bool succes = dict.try_get_value(folder_id, result);
		return result;
	}
	catch (std::exception) {
		return result;
	}
}

std::string FileManager::GetWorkingDir()
{
	std::filesystem::path path = std::filesystem::current_path();
	std::string output = path.u8string();
	return output;
}



bool FileManager::CheckFileExistance(std::string folder_id, std::string file)
{
	std::string result = CombinePath(folder_id, file);
	if (result == "") {
		return false;
	}
	std::fstream stream;

	stream.open(result, stream.in);
	if (stream.fail()) {
		return false;
	}
	stream.close();
	return true;
}

std::string FileManager::CombinePath(std::string folder_id, std::string file)
{
	std::string result = GetDirectory(folder_id);
	if (result.empty()) {
		return "";
	}
	std::string total_path = result;
	total_path += "\\";
	total_path += file;
	return total_path;
}

bool FileManager::CreateFile(std::string folder_id, std::string filename)
{
	if (CheckFileExistance(folder_id, filename)) {
		return false;
	}
	throw std::exception();
	return true;
}

std::string FileManager::ReadTextFile(std::string folder_id, std::string filename)
{
	if (CheckFileExistance(folder_id, filename)) {
		std::string result = CombinePath(folder_id, filename);
		if (result == "") {
			return "";
		}
		std::fstream stream;
		std::stringstream ss;

		stream.open(result, stream.in);
		if (stream.fail()) {
			stream.close();
			return "";
		}
		ss << stream.rdbuf();
		stream.close();
		return ss.str();
	}
	return "";
}

bool FileManager::WriteStringToFile(std::string folder_id, std::string filename, std::string content, bool trunc)
{
	if (!CheckFileExistance(folder_id, filename)) {
		std::string result = CombinePath(folder_id, filename);
		if (result == "") {
			return "";
		}

		std::fstream stream;
		if(trunc)
			stream.open(result, stream.out | stream.trunc);
		else
			stream.open(result, stream.out);
		if (stream.fail()) {
			stream.flush();
			stream.close();
			return false;
		}
		stream << content;
		stream.flush();
		stream.close();
		return true;
	}
	return false;
}

bool FileManager::WriteDataToFile(std::string folder_id, std::string filename, char* data, size_t size, bool trunc)
{
	if (!CheckFileExistance(folder_id, filename)) {
		std::string result = CombinePath(folder_id, filename);
		if (result == "") {
			return "";
		}

		std::fstream stream;
		if (trunc)
			stream.open(result, stream.out | stream.trunc);
		else
			stream.open(result, stream.out);
		if (stream.fail()) {
			stream.flush();
			stream.close();
			return false;
		}
		stream.write(data, size);
		stream.flush();
		stream.close();
		return true;
	}
	return false;
}

bool FileManager::ImportObjFile(std::string folder_id, std::string filename, std::vector<Primitive>& result)
{
	result.clear();
	std::string inputfile = CombinePath(folder_id, filename);
	std::string basedir = GetDirectory(folder_id);
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::vector<VertexData> components;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str(), basedir.c_str() , true, true);
	if (!warn.empty()) {
		std::cout << warn << std::endl;
	}
	if (!err.empty()) {
		std::cout << err << std::endl;
	}

	if (!ret) {
		return false;
	}
	try {
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < (size_t)fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
					tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
					tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
					tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
					tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
					tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
					tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];

					glm::vec3 vertex(vx, vy, vz);
					glm::vec3 normal(nx, nx, vz);
					glm::vec3 texture(tx, ty, 0.0f);
					components.push_back({
						vertex,
						normal,
						texture });
				}
				index_offset += fv;
			}
		}
		for (size_t i = 0; i < components.size(); i += 3) {
			result.push_back({ components[i], components[i + 1], components[i + 2] });
		}
	}
	catch (std::exception e) {
		throw e;
	}
	return true;
}
