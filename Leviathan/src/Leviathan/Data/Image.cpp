#include "Image.h"
#include "stb-master/stb_image.h"

namespace leviathan {
	Image::Image(int width, int height, int channels, unsigned char* data)
	{
		this->width = width;
		this->height = height;
		this->channels = channels;
		this->data = data;
	}

	Image::~Image()
	{
		stbi_image_free(this->data);
	}

	void Image::GetDimensions(int* width, int* height)
	{
		*width = this->width;
		*height = this->height;
	}
	std::shared_ptr<Image> Image::Load(std::string folder_id, std::string file)
	{
		if (FileManager::CheckFileExistance(folder_id, file)) {
			std::string result = FileManager::GetDirectory(folder_id);
			if (result.empty()) {
				return false;
			}
			std::string total_path = result;
			total_path += "\\";
			total_path += file;

			int width, height, channels;
			unsigned char* data = stbi_load(total_path.c_str(), &width, &height, &channels, 4);
			if (data) {
				return std::make_shared<Image>(width, height, channels, data);
			}
			return nullptr;
		}
		return nullptr;
	}
	unsigned char* Image::Load(std::string folder_id, std::string file, int* width, int* height, int* channels)
	{
		if (FileManager::CheckFileExistance(folder_id, file)) {
			std::string result = FileManager::GetDirectory(folder_id);
			if (result.empty()) {
				return false;
			}
			std::string total_path = result;
			total_path += "\\";
			total_path += file;

			unsigned char* data = stbi_load(total_path.c_str(), width, height, channels, 4);
			return data;
		}
		return nullptr;
	}
}
