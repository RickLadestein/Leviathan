#include "FileManager.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstddef>
#include <filesystem>

using leviathan::Image;

std::unordered_map<std::string, std::string> dirs;

bool FileManager::RegisterDirectory(std::string folder_id, std::string path, bool overwrite)
{
	try {
		std::string res = dirs.at(folder_id);
		if (overwrite) {
			dirs[folder_id] = path;
			return true;
		}
		return false;
	}
	catch (std::out_of_range eor) {
		dirs[folder_id] = path;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

bool FileManager::UnregisterDirectory(std::string folder_id)
{
	try {
		std::string result = dirs.at(folder_id);
		dirs.erase(folder_id);
		return true;
	}
	catch (std::out_of_range eor) {
		return false;
	}
	return false;
}

std::string FileManager::GetWorkingDir()
{
	std::filesystem::path path = std::filesystem::current_path();
	std::string output = path.u8string();
	return output;
}

std::string FileManager::GetDirectory(std::string folder_id)
{
	try {
		std::string result = dirs.at(folder_id);
		return result;
	}
	catch (std::exception e) {
		return "";
	}
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
