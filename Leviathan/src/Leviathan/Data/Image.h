#pragma once
#include "Leviathan/Util/FileManager.h"

#include <memory>
#include <string>
namespace Leviathan {
	class Image {
	public:
		Image(int width, int height, int channels, unsigned char* data);
		~Image();

		void GetDimensions(int* width, int* height);
		inline int GetChannelCount() { return this->channels; };
		inline unsigned char* GetDataPtr() { return this->data; };

		Image() = delete;
		Image(const Image&) = delete;
		Image& operator=(const Image&) = delete;

		static std::shared_ptr<Image> Load(std::string folder_id, std::string file, bool flip = false);
		static unsigned char* Load(std::string folder_id, std::string file, int* width, int* height, int* channels, bool flip = false);
	private:
		int width, height, channels;
		unsigned char* data;
	};
}