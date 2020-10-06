#pragma once
#include "Leviathan/Data/Image.h"
#include "Leviathan/Data/Structures.h"

#include <string>
#include <vector>

class FileManager {
public:
	static bool RegisterDirectory(std::string folder_id, std::string path, bool overwrite = true);
	static bool UnregisterDirectory(std::string folder_id);
	static std::string GetWorkingDir();
	static std::string GetDirectory(std::string folder_id);
	static bool CheckFileExistance(std::string folder_id, std::string file);
	static std::string CombinePath(std::string folder_id, std::string file);

	static bool CreateFile(std::string folder_id, std::string filename);
	static std::string ReadTextFile(std::string folder_id, std::string filename);
	static bool WriteStringToFile(std::string folder_id, std::string filename, std::string content, bool trunc = true);
	static bool WriteDataToFile(std::string folder_id, std::string filename, char* data, size_t size, bool trunc = true);

	static bool ImportObjFile(std::string folder_id, std::string filename, std::vector<Primitive>& result);
};